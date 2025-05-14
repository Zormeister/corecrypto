//
//  ccblowfish_ltc.c
//  corecrypto
//
//  Created by Zormeister on 12/5/2025.
//

#include "ccblowfish_ltc_internal.h"
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccblowfish.h>
#include <corecrypto/ccmode_impl.h>

// Thank you so much to Tom St Denis for the implementation for the Blowfish cipher
// LibTomCrypt is licensed under the unlicense.

#ifndef __GNUC__
#define F(x) ((S1[cc_byte(x,3)] + S2[cc_byte(x,2)]) ^ S3[cc_byte(x,1)]) + S4[cc_byte(x,0)]
#else
#define F(x) ((skey->S[0][cc_byte(x,3)] + skey->S[1][cc_byte(x,2)]) ^ skey->S[2][cc_byte(x,1)]) + skey->S[3][cc_byte(x,0)]
#endif

static uint32_t s_blowfish_stream2word(const unsigned char *d, int dlen, int *cur)
{
   unsigned int z;
   int y = *cur;
   uint32_t ret = 0;

   for (z = 0; z < 4; z++) {
       ret = (ret << 8) | ((uint32_t)d[y++] & 255);
       if (y == dlen) {
          y = 0;
       }
   }

   *cur = y;
   return ret;
}

int ccblowfish_ltc_ecb_encrypt(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out)
{
   uint32_t L, R;
   const struct ccblowfish_ltc_ctx *skey = (const struct ccblowfish_ltc_ctx *)ctx;

   const void *cur_in = in;
   void *cur_out = out;

   while (nblocks--) {
       CC_LOAD32_LE(R, cur_in);
       CC_LOAD32_LE(L, cur_in+4);

#ifndef __GNUC__
        const uint32_t *S1, *S2, *S3, *S4;

        S1 = skey->S[0];
        S2 = skey->S[1];
        S3 = skey->S[2];
        S4 = skey->S[3];
#endif

        /* do 16 rounds */
        for (int rounds = 0; rounds < 16; ) {
            L ^= skey->K[rounds++];  R ^= F(L);
            R ^= skey->K[rounds++];  L ^= F(L);
            L ^= skey->K[rounds++];  R ^= F(L);
            R ^= skey->K[rounds++];  L ^= F(L);
        }

        /* last keying */
        L ^= skey->K[16];
        R ^= skey->K[17];

       CC_STORE32_LE(R, cur_out);
       CC_STORE32_LE(L, cur_out+4);

       cur_in += CCBLOWFISH_BLOCK_SIZE;
       cur_out += CCBLOWFISH_BLOCK_SIZE;
   }

   return CCERR_OK;
}

int ccblowfish_ltc_ecb_decrypt(const ccecb_ctx *ctx, size_t nblocks, const void *in, void *out)
{
   uint32_t L, R;
   const struct ccblowfish_ltc_ctx *skey = (const struct ccblowfish_ltc_ctx *)ctx;

   const void *cur_in = in;
   void *cur_out = out;

#ifndef __GNUC__
   const uint32_t *S1, *S2, *S3, *S4;
#endif

#ifndef __GNUC__
    S1 = skey->S[0];
    S2 = skey->S[1];
    S3 = skey->S[2];
    S4 = skey->S[3];
#endif

    while (nblocks--) {
        CC_LOAD32_LE(R, cur_in);
        CC_LOAD32_LE(L, cur_in+4);

        R ^= skey->K[17];
        L ^= skey->K[16];

        for (int r = 15; r > 0; ) {
           L ^= F(R); R ^= skey->K[r--];
           R ^= F(L); L ^= skey->K[r--];
           L ^= F(R); R ^= skey->K[r--];
           R ^= F(L); L ^= skey->K[r--];
        }

        CC_STORE32_LE(R, cur_out);
        CC_STORE32_LE(L, cur_out+4);

        cur_in += CCBLOWFISH_BLOCK_SIZE;
        cur_out += CCBLOWFISH_BLOCK_SIZE;
    }

    return CCERR_OK;
}

int ccblowfish_ltc_setup(const struct ccmode_ecb *ecb, ccecb_ctx *ctx, size_t key_len, const void *key)
{
   struct ccblowfish_ltc_ctx *skey = (struct ccblowfish_ltc_ctx *)ctx;
   cc_memcpy(skey->K, ORIG_P, sizeof(ORIG_P));
   cc_memcpy(skey->S, ORIG_S, sizeof(ORIG_S));

   uint32_t x, y, A, B[2];
   int i;

   /* load in key bytes (Supplied by David Hopwood) */
   i = 0;
   for (x = 0; x < 18; x++) {
       A = s_blowfish_stream2word(key, key_len, &i);
       skey->K[x] ^= A;
   }


   i = 0;
   B[0] = 0;
   B[1] = 0;
   for (x = 0; x < 18; x += 2) {
      /* encrypt it */
      ccblowfish_ltc_ecb_encrypt((ccecb_ctx *)skey, 1, B, B);
      /* copy it */
      skey->K[x] = B[0];
      skey->K[x+1] = B[1];
   }

   /* encrypt S array */
   for (x = 0; x < 4; x++) {
       for (y = 0; y < 256; y += 2) {
          /* encrypt it */
          ccblowfish_ltc_ecb_encrypt((ccecb_ctx *)skey, 1, B, B);
          /* copy it */
          skey->S[x][y] = B[0];
          skey->S[x][y+1] = B[1];
       }
   }

   return CCERR_OK;
}

const struct ccmode_ecb ccblowfish_ltc_ecb_encrypt_mode = {
    .size = sizeof(struct ccblowfish_ltc_ctx),
    .block_size = CCBLOWFISH_BLOCK_SIZE,
    .init = ccblowfish_ltc_setup,
    .ecb = ccblowfish_ltc_ecb_encrypt,
};

const struct ccmode_ecb ccblowfish_ltc_ecb_decrypt_mode = {
    .size = sizeof(struct ccblowfish_ltc_ctx),
    .block_size = CCBLOWFISH_BLOCK_SIZE,
    .init = ccblowfish_ltc_setup,
    .ecb = ccblowfish_ltc_ecb_decrypt,
};
