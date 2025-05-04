#include "../include/pqc_define.h"
#include "../include/pqc_extern.h"
#include "../include/pqc_return.h"

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

    int ret;

    // 매개변수 검증
    if (pk == NULL || sk == NULL) {
        return PQC_NULL_POINTER_ERROR;
    }


    switch (algorithm) {
        case ALG_MLKEM512:
            ret = PQCLEAN_MLKEM512_CLEAN_crypto_kem_keypair(pk, sk);
            // 조건부 (ret == 0), 조건이 참이면 왼쪽 값 반환, 조건이 거짓이면 오른쪽 값 반환.
            // kem_keypair 돌렸을때 참이면 0으로 반환함.
            return (ret == 0) ? ML_KEM_512_KEYPAIR_SUCCESS : ML_KEM_512_KEYPAIR_FAIL;

        case ALG_MLKEM768:
            ret = PQCLEAN_MLKEM768_CLEAN_crypto_kem_keypair(pk, sk);
            return (ret == 0) ? ML_KEM_768_KEYPAIR_SUCCESS : ML_KEM_768_KEYPAIR_FAIL;

        case ALG_MLKEM1024:
            ret = PQCLEAN_MLKEM1024_CLEAN_crypto_kem_keypair(pk, sk);
            return (ret == 0) ? ML_KEM_1024_KEYPAIR_SUCCESS : ML_KEM_1024_KEYPAIR_FAIL;

        default:
            return PQC_UNSUPPORTED_ALGORITHM;
    }
}

int Kem_Encapsulate(
    uint8_t *ct,
    uint8_t *ss,
    const uint8_t *pk,
    unsigned int algorithm) {
    
    int ret;

    // 매개변수 검증
    if (ct == NULL || ss == NULL || pk == NULL) {
        return PQC_NULL_POINTER_ERROR;
    }

    switch (algorithm) {
    case ALG_MLKEM512:
        ret = PQCLEAN_MLKEM512_CLEAN_crypto_kem_enc(ct, ss, pk);
        return (ret == 0) ? ML_KEM_512_ENCAP_SUCCESS : ML_KEM_512_ENCAP_FAIL;

    case ALG_MLKEM768:
        ret = PQCLEAN_MLKEM768_CLEAN_crypto_kem_enc(ct, ss, pk);
        return (ret == 0) ? ML_KEM_768_ENCAP_SUCCESS : ML_KEM_768_ENCAP_FAIL;

    case ALG_MLKEM1024:
        ret = PQCLEAN_MLKEM1024_CLEAN_crypto_kem_enc(ct, ss, pk);
        return (ret == 0) ? ML_KEM_1024_ENCAP_SUCCESS : ML_KEM_1024_ENCAP_FAIL;

    default:
        return PQC_UNSUPPORTED_ALGORITHM;
    }
}
 
int Kem_Decapsulate(
    uint8_t *ss,
    const uint8_t *ct,
    const uint8_t *sk,
    unsigned int algorithm) {
    
    int ret;

    // 매개 변수 검증
    if (ss == NULL || ct == NULL || sk == NULL) {
        return PQC_NULL_POINTER_ERROR;
    }

    switch(algorithm) {
        case ALG_MLKEM512:
            ret = PQCLEAN_MLKEM512_CLEAN_crypto_kem_dec(ss, ct, sk);
            return (ret == 0) ? ML_KEM_512_DECAP_SUCCESS : ML_KEM_512_DECAP_FAIL;

        case ALG_MLKEM768:
            ret = PQCLEAN_MLKEM768_CLEAN_crypto_kem_dec(ss, ct, sk);
            return (ret == 0) ? ML_KEM_768_DECAP_SUCCESS : ML_KEM_768_DECAP_FAIL;

        case ALG_MLKEM1024:
            ret = PQCLEAN_MLKEM1024_CLEAN_crypto_kem_dec(ss, ct, sk);
            return (ret == 0) ? ML_KEM_1024_DECAP_SUCCESS : ML_KEM_1024_DECAP_FAIL;

        default: 
            return PQC_UNSUPPORTED_ALGORITHM;
    }
}

int Sign_Keypair(
    uint8_t *pk,
    uint8_t *sk,
    unsigned int algorithm) {
    
    int ret;

    // 매개변수 검증
    if (pk == NULL || sk == NULL) {
        return PQC_NULL_POINTER_ERROR;
    }

    switch(algorithm) {
        case ALG_MLDSA44:
            ret = PQCLEAN_MLDSA44_CLEAN_crypto_sign_keypair(pk, sk);
            return (ret == 0) ? ML_DSA_44_KEYPAIR_SUCCESS : ML_DSA_44_KEYPAIR_FAIL;

        case ALG_MLDSA65:
            ret = PQCLEAN_MLDSA65_CLEAN_crypto_sign_keypair(pk, sk);
            return (ret == 0) ? ML_DSA_65_KEYPAIR_SUCCESS : ML_DSA_65_KEYPAIR_FAIL;

        case ALG_MLDSA87:
            ret = PQCLEAN_MLDSA87_CLEAN_crypto_sign_keypair(pk, sk);
            return (ret == 0) ? ML_DSA_87_KEYPAIR_SUCCESS : ML_DSA_87_KEYPAIR_FAIL;

        default:
            return PQC_UNSUPPORTED_ALGORITHM;
    }
}
 
int Sign_Signature(
    uint8_t *sig,
    size_t *siglen,
    const uint8_t *m,
    size_t mlen,
    const uint8_t *sk,
    unsigned int algorithm) {
    
    int ret;

    // 매개변수 검증
    if (sig == NULL || siglen == NULL || m == NULL || sk == NULL) {
        return PQC_NULL_POINTER_ERROR;
    }

    switch(algorithm) {
        case ALG_MLDSA44:
            ret = PQCLEAN_MLDSA44_CLEAN_crypto_sign_signature(sig, siglen, m, mlen, sk);
            return (ret == 0) ? ML_DSA_44_SIGN_SUCCESS : ML_DSA_44_SIGN_FAIL;

        case ALG_MLDSA65:
            ret = PQCLEAN_MLDSA65_CLEAN_crypto_sign_signature(sig, siglen, m, mlen, sk);
            return (ret == 0) ? ML_DSA_65_SIGN_SUCCESS : ML_DSA_65_SIGN_FAIL;

        case ALG_MLDSA87:
            ret = PQCLEAN_MLDSA87_CLEAN_crypto_sign_signature(sig, siglen, m, mlen, sk);
            return (ret == 0) ? ML_DSA_87_SIGN_SUCCESS : ML_DSA_87_SIGN_FAIL;

        default:
            return PQC_UNSUPPORTED_ALGORITHM;
    }
}

int Sign_Verify(
    const uint8_t *sig,
    size_t siglen,
    const uint8_t *m,
    size_t mlen,
    const uint8_t *pk,
    unsigned int algorithm) {
    
    int ret;

    // 매개변수 검증
    if (sig == NULL || m == NULL || pk == NULL) {
        return PQC_NULL_POINTER_ERROR;
    }

    switch(algorithm) {
        case ALG_MLDSA44:
            ret = PQCLEAN_MLDSA44_CLEAN_crypto_sign_verify(sig, siglen, m, mlen, pk);
            return (ret == 0) ? ML_DSA_44_VERIFY_SUCCESS : ML_DSA_44_VERIFY_FAIL;

        case ALG_MLDSA65:
            ret = PQCLEAN_MLDSA65_CLEAN_crypto_sign_verify(sig, siglen, m, mlen, pk);
            return (ret == 0) ? ML_DSA_65_VERIFY_SUCCESS : ML_DSA_65_VERIFY_FAIL;

        case ALG_MLDSA87:
            ret = PQCLEAN_MLDSA87_CLEAN_crypto_sign_verify(sig, siglen, m, mlen, pk);
            return (ret == 0) ? ML_DSA_87_VERIFY_SUCCESS : ML_DSA_87_VERIFY_FAIL;

        default:
            return PQC_UNSUPPORTED_ALGORITHM;
    }
}
