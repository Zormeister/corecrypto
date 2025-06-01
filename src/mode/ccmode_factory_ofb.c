//
//  ccmode_factory_ofb.c
//  corecrypto
//
//  Created by Zormeister on 30/5/2025.
//

#include <corecrypto/cc.h>
#include <corecrypto/cc_priv.h>
#include <corecrypto/ccmode_factory.h>

#define CCMODE_OFB_IV(okey) okey->u
#define CCMODE_OFB_ECB_CTX(okey) (ccecb_ctx *)okey->u + ccn_sizeof_size(okey->ecb->block_size)

/* 
 * so this uses the pad_len field as a tracker for the current index within the block 
 * to avoid having to do extra work if the nbytes isn't aligned with the block size.
 */

int ccmode_ofb_init(const struct ccmode_ofb *ofb, ccofb_ctx *ctx, size_t rawkey_len, const void *rawkey, const void *iv) {
    struct _ccmode_ofb_key *okey = (struct _ccmode_ofb_key *)ctx;
    okey->ecb = (const struct ccmode_ecb *)ofb->custom;
    cc_memcpy(CCMODE_OFB_IV(okey), iv, okey->ecb->block_size);
    okey->ecb->init(okey->ecb, CCMODE_OFB_ECB_CTX(okey), rawkey_len, rawkey);
    /* don't want to cause a disaster, see ccmode_ofb_crypt. */
    okey->pad_len = okey->ecb->block_size;
    return CCERR_OK;
}

int ccmode_ofb_crypt(ccofb_ctx *ctx, size_t nbytes, const void *in, void *out) {
    struct _ccmode_ofb_key *okey = (struct _ccmode_ofb_key *)ctx;

    /* way more efficient than just cycling it by block. maybe i should do this for other impls. */
    for (size_t i = 0; i < nbytes; i++) {
        if (okey->pad_len == okey->ecb->block_size) {
            okey->ecb->ecb(CCMODE_OFB_ECB_CTX(okey), 1, CCMODE_OFB_IV(okey), CCMODE_OFB_IV(okey));
            okey->pad_len = 0;
        }

        cc_xor(1, (out + i), CCMODE_OFB_IV(okey) + okey->pad_len, (in + i)); /* tbf i could have just done a normal XOR rather than this bs but whatever. */
        okey->pad_len++;
    }

    return CCERR_OK;
}

void ccmode_factory_ofb_crypt(struct ccmode_ofb *ofb, const struct ccmode_ecb *ecb) {
    ofb->size = ccn_sizeof_size(sizeof(struct _ccmode_ofb_key)) + ccn_sizeof_size(ecb->block_size) + ccn_sizeof_size(ecb->size);
    ofb->block_size = 1;
    ofb->init = ccmode_ofb_init;
    ofb->ofb = ccmode_ofb_crypt;
    ofb->custom = ecb;
}
