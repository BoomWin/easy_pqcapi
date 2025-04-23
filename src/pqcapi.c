#include "../include/pqc_define.h"
#include "../include/pqc_extern.h"

// ML-KEM 관련 헤더 포함
#include "../crypto_kem/ml-kem-512/api.h"
#include "../crypto_kem/ml-kem-768/api.h"
#include "../crypto_kem/ml-kem-1024/api.h"

// ML-DSA 관련 헤더 포함
#include "../crypto_sign/ml-dsa-44/api.h"
#include "../crypto_sign/ml-dsa-65/api.h"
#include "../crypto_sign/ml-dsa-87/api.h"

int Kem_Keypair(
    uint8_t *pk,
    uint8_t *sk,
    unsigned int algorithm) {

    int ret = DEFAULT_ERROR;

    switch (algorithm) {
        case ALG_MLKEM512:
            ret = PQCLEAN_MLKEM512_CLEAN_crypto_kem_keypair(pk, sk);
            break;
        case ALG_MLKEM768:
            ret = PQCLEAN_MLKEM768_CLEAN_crypto_kem_keypair(pk, sk);
            break;
        case ALG_MLKEM1024:
            ret = PQCLEAN_MLKEM1024_CLEAN_crypto_kem_keypair(pk, sk);
            break;
        default:
            return DEFAULT_ERROR;
    }
    return (ret == 0) ? OK : DEFAULT_ERROR;
}

int Kem_Encapsulate(
    uint8_t *ct,
    uint8_t *ss,
    const uint8_t *pk,
    unsigned int algorithm) {
    
    int ret = DEFAULT_ERROR;

    switch (algorithm) {
    case ALG_MLKEM512:
        ret = PQCLEAN_MLKEM512_CLEAN_crypto_kem_enc(ct, ss, pk);
        break;
    case ALG_MLKEM768:
        ret = PQCLEAN_MLKEM768_CLEAN_crypto_kem_enc(ct, ss, pk);
        break;
    case ALG_MLKEM1024:
        ret = PQCLEAN_MLKEM1024_CLEAN_crypto_kem_enc(ct, ss, pk);
        break;
    default:
        return DEFAULT_ERROR;
    }
    return (ret == 0) ? OK : DEFAULT_ERROR;
}
 
int Kem_Decapsulate(
    uint8_t *ss,
    const uint8_t *ct,
    const uint8_t *sk,
    unsigned int algorithm) {
    
    int ret = DEFAULT_ERROR;

    switch(algorithm) {
        case ALG_MLKEM512:
            ret = PQCLEAN_MLKEM512_CLEAN_crypto_kem_dec(ss, ct, sk);
            break;
        case ALG_MLKEM768:
            ret = PQCLEAN_MLKEM768_CLEAN_crypto_kem_dec(ss, ct, sk);
            break;
        case ALG_MLKEM1024:
            ret = PQCLEAN_MLKEM1024_CLEAN_crypto_kem_dec(ss, ct, sk);
            break;
        default:
            return DEFAULT_ERROR;
    }
    return (ret == 0) ? OK : DEFAULT_ERROR;
}

int Sign_Keypair(
    uint8_t *pk,
    uint8_t *sk,
    unsigned int algorithm) {
    
    int ret = DEFAULT_ERROR;

    switch(algorithm) {
        case ALG_MLDSA44:
            ret = PQCLEAN_MLDSA44_CLEAN_crypto_sign_keypair(pk, sk);
            break;
        case ALG_MLDSA65:
            ret = PQCLEAN_MLDSA65_CLEAN_crypto_sign_keypair(pk, sk);
            break;
        case ALG_MLDSA87:
            ret = PQCLEAN_MLDSA87_CLEAN_crypto_sign_keypair(pk, sk);
            break;
        default:
            return DEFAULT_ERROR;
    }
    return (ret == 0) ? OK : DEFAULT_ERROR;
}
 
int Sign_Signature(
    uint8_t *sig,
    size_t *siglen,
    const uint8_t *m,
    size_t mlen,
    const uint8_t *sk,
    unsigned int algorithm) {
    
    int ret = DEFAULT_ERROR;

    switch(algorithm) {
        case ALG_MLDSA44:
            ret = PQCLEAN_MLDSA44_CLEAN_crypto_sign_signature(sig, siglen, m, mlen, sk);
            break;
        case ALG_MLDSA65:
            ret = PQCLEAN_MLDSA65_CLEAN_crypto_sign_signature(sig, siglen, m, mlen, sk);
            break;
        case ALG_MLDSA87:
            ret = PQCLEAN_MLDSA87_CLEAN_crypto_sign_signature(sig, siglen, m, mlen, sk);
            break;
        default:
            return DEFAULT_ERROR;
    }
    return (ret == 0) ? OK : DEFAULT_ERROR;
}

int Sign_Verify(
    const uint8_t *sig,
    size_t siglen,
    const uint8_t *m,
    size_t mlen,
    const uint8_t *pk,
    unsigned int algorithm) {
    
    int ret = DEFAULT_ERROR;

    switch(algorithm) {
        case ALG_MLDSA44:
            ret = PQCLEAN_MLDSA44_CLEAN_crypto_sign_verify(sig, siglen, m, mlen, pk);
            break;
        case ALG_MLDSA65:
            ret = PQCLEAN_MLDSA65_CLEAN_crypto_sign_verify(sig, siglen, m, mlen, pk);
            break;
        case ALG_MLDSA87:
            ret = PQCLEAN_MLDSA87_CLEAN_crypto_sign_verify(sig, siglen, m, mlen, pk);
            break;
        default:
            return DEFAULT_ERROR;
    }
    return (ret == 0) ? OK : DEFAULT_ERROR;
}
