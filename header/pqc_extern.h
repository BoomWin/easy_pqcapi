#ifndef _PQC_EXTERN_H_
#define _PQC_EXTERN_H_

#include <stdint.h>
#include <stddef.h>

// KEM 관련 함수 (ML-KEM)
extern int Kem_Keypair(
    uint8_t *pk,
    uint8_t *sk,
    unsigned int algorithm);

extern int Kem_Encapsulate(
    uint8_t *ct,
    uint8_t *ss,
    const uint8_t *pk,
    unsigned int algorithm);

extern int Kem_Decapsulate(
    uint8_t *ss,
    const uint8_t *ct,
    const uint8_t *sk,
    unsigned int algorithm);


// 서명 관련 함수 (ML-DSA)
extern int Sign_Keypair(
    uint8_t *pk,
    uint8_t *sk,
    unsigned int algorithm);

extern int Sign_Signature(
    uint8_t *sig,
    size_t *siglen,
    const uint8_t *m,
    size_t mlen,
    const uint8_t *sk,
    unsigned int algorithm);













#endif // _PQC_EXTERN_H_