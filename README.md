
# libpqcapi - 양자 내성 암호 API 라이브러리

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![Version](https://img.shields.io/badge/version-1.0-green.svg)

**libpqcapi**는 NIST 표준에 따라 설계된 포스트 양자 암호(PQC) 알고리즘 구현 라이브러리입니다.  
ML-KEM(Kyber 기반)과 ML-DSA(Dilithium 기반)를 지원하여 안전한 키 교환과 디지털 서명을 제공합니다.    
해당 라이브러리의 암호 기능을 담당하는 핵심 연산부는 PQCLEAN을 사용하여 제작하였습니다.

---

## 🔐 지원 알고리즘

### ML-KEM (Key Encapsulation Mechanism)

| 알고리즘     | 보안 수준   | 공개키 | 비밀키 | 암호문 | 공유 비밀 |
|--------------|-------------|--------|--------|--------|------------|
| ML-KEM-512   | NIST Level 1 | 800 B  | 1632 B | 768 B  | 32 B       |
| ML-KEM-768   | NIST Level 3 | 1184 B | 2400 B | 1088 B | 32 B       |
| ML-KEM-1024  | NIST Level 5 | 1568 B | 3168 B | 1568 B | 32 B       |

### ML-DSA (Digital Signature Algorithm)

| 알고리즘     | 보안 수준   | 공개키 | 비밀키 | 서명 크기 |
|--------------|-------------|--------|--------|------------|
| ML-DSA-44    | NIST Level 1 | 1312 B | 2560 B | 2420 B     |
| ML-DSA-65    | NIST Level 3 | 1952 B | 4032 B | 3309 B     |
| ML-DSA-87    | NIST Level 5 | 2592 B | 4896 B | 4627 B     |

---

## 💻 지원 플랫폼

| 플랫폼 코드 | 설명 |
|-------------|------|
| x64_linux_type1 | Ubuntu 20.04 |
| x64_linux_type2 | Ubuntu 22.04 |
| x64_linux_type3 | Ubuntu 24.04 |
| armv7l_linux_type1 | DUSS |
| armv7l_linux_type2 | LTE |
| armv7l_linux_type3 | Raspberry Pi 4.19 |
| armv7l_linux_type4 | Raspberry Pi 4.9 |
| armv7l_linux_type5 | Raspberry Pi 5.10 |
| armv7l_linux_type6 | SAMA7G54-EK 5.15 |
| armv7l_linux_type7 | Raspberry Pi 6.6 |
| aarch64_linux_type1 | Raspberry Pi 4.9 (64bit) |
| aarch64_linux_type2 | Raspberry Pi 5.10 (64bit) |

---

## 📦 설치 방법
- 배포 문서 참조-

