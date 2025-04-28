CC = gcc
CFLAGS = -Wall -Wextra -O3 -fPIC
LDFLAGS = -shared

# 디렉토리 정의
SRC_DIR = src
INCLUDE_DIR = include
KEM_DIR = crypto_kem
SIGN_DIR = crypto_sign
COMMON_DIR = common

# 포함 디렉토리
INCLUDES = -I$(INCLUDE_DIR) \
           -I$(KEM_DIR)/ml-kem-512 -I$(KEM_DIR)/ml-kem-768 -I$(KEM_DIR)/ml-kem-1024 \
           -I$(SIGN_DIR)/ml-dsa-44 -I$(SIGN_DIR)/ml-dsa-65 -I$(SIGN_DIR)/ml-dsa-87 \
           -I$(COMMON_DIR)

# PQC API 소스 파일
PQCAPI_SRC = $(SRC_DIR)/pqcapi.c

# ML-KEM 소스 파일
KEM_512_SRC = $(wildcard $(KEM_DIR)/ml-kem-512/*.c)
KEM_768_SRC = $(wildcard $(KEM_DIR)/ml-kem-768/*.c)
KEM_1024_SRC = $(wildcard $(KEM_DIR)/ml-kem-1024/*.c)

# ML-DSA 소스 파일
DSA_44_SRC = $(wildcard $(SIGN_DIR)/ml-dsa-44/*.c)
DSA_65_SRC = $(wildcard $(SIGN_DIR)/ml-dsa-65/*.c)
DSA_87_SRC = $(wildcard $(SIGN_DIR)/ml-dsa-87/*.c)

# 공통 소스 파일
COMMON_SRC = $(wildcard $(COMMON_DIR)/*.c)
#  $(wildcard $(COMMON_DIR)/keccak2x/*.c) $(wildcard $(COMMON_DIR)/keccak4x/*.c)

# 소스 파일 통합
ALL_SRC = $(PQCAPI_SRC) $(KEM_512_SRC) $(KEM_768_SRC) $(KEM_1024_SRC) $(DSA_44_SRC) $(DSA_65_SRC) $(DSA_87_SRC) $(COMMON_SRC)

# 목적 파일
OBJS = $(ALL_SRC:.c=.o)

# 라이브러리 이름
LIB_NAME = libpqcapi.so
LIB_VERSION = 1.0.0
LIB_SONAME = $(LIB_NAME).1
LIB_FULL = $(LIB_NAME).$(LIB_VERSION)

# 기본 타겟
all: $(LIB_FULL)

# 공유 라이브러리 빌드
$(LIB_FULL): $(OBJS)
	$(CC) $(LDFLAGS) -Wl,-soname,$(LIB_SONAME) -o $@ $^
	ln -sf $(LIB_FULL) $(LIB_SONAME)
	ln -sf $(LIB_SONAME) $(LIB_NAME)

# 소스 컴파일
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 정적 라이브러리 빌드
static: $(OBJS)
	ar rcs libpqcapi.a $(OBJS)

# 테스트 빌드
test: $(LIB_FULL)
	$(CC) $(CFLAGS) $(INCLUDES) -o test/test_pqcapi test/test_pqcapi.c -L. -lpqcapi

# 설치 (시스템 라이브러리 경로에 설치)
install: $(LIB_FULL)
	install -d $(DESTDIR)/usr/lib
	install -d $(DESTDIR)/usr/include
	install -m 755 $(LIB_FULL) $(DESTDIR)/usr/lib
	ln -sf $(LIB_FULL) $(DESTDIR)/usr/lib/$(LIB_SONAME)
	ln -sf $(LIB_SONAME) $(DESTDIR)/usr/lib/$(LIB_NAME)
	install -m 644 $(INCLUDE_DIR)/pqc_define.h $(DESTDIR)/usr/include
	install -m 644 $(INCLUDE_DIR)/pqc_extern.h $(DESTDIR)/usr/include
	ldconfig


# 라이브러리 파일과 라이브러리 헤더만 복사하기
pack:
	mkdir -p pqcapi_lib/include
	cp $(LIB_FULL) $(LIB_SONAME) $(LIB_NAME) libpqcapi.a pqcapi_lib/ 2>/dev/null || true
	cp $(INCLUDE_DIR)/pqc_define.h $(INCLUDE_DIR)/pqc_extern.h pqcapi_lib/include/

# 정리
clean:
	rm -f $(OBJS) $(LIB_FULL) $(LIB_SONAME) $(LIB_NAME) libpqcapi.a test/test_pqcapi
	rm -rf pqcapi_lib

.PHONY: all static test install pack clean