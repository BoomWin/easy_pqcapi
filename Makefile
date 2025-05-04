# KMULIB V2.2 참고해서 Makefile 작성


# 패키지 및 라이브러리 정보
PACKAGE_NAME = libpqcapi
PACKAGE_VERSION = 1.0
PACKAGE_DIR = package
VERSION = 1.0

# 플랫폼 설정 (기본값은 직접 명령어로 선택하도록 함)
PLATFORM ?= unknown_platform

# 대상 파일명
TARGET_SO = $(PACKAGE_NAME)_$(PACKAGE_VERSION)-$(PLATFORM).so

# 지원되는 모든 플랫폼
SUPPORTED_PLATFORMS = x64_linux_type1 x64_linux_type2 x64_linux_type3 \
					armv7l_linux_type1 armv7l_linux_type2 armv7l_linux_type3 \
					armv7l_linux_type4 armv7l_linux_type5 armv7l_linux_type6 \
					armv7l_linux_type7 \
					aarch64_linux_type1 aarch64_linux_type2

# 플랫폼별 컴파일러 및 플래그 설정
define set_platform_x64_linux_type1
	PLATFORM_DESC = Ubuntu 20.04
	CROSS_COMPILE =
	CFLAGS_PLATFORM = -march=x86-64
endef

define set_platform_x64_linux_type2
	PLATFORM_DESC = Ubuntu 22.04
	CROSS_COMPILE = 
	CFLAGS_PLATFORM = -march=x86-64 -mtune=generic
endef

define set_platform_x64_linux_type3
	PLATFORM_DESC = Ubuntu 24.04
	CROSS_COMPILE = 
	CFLAGS_PLATFORM = -march=x86-64-v3
endef

define set_platform_armv7l_linux_type1
    PLATFORM_DESC = DUSS
    CROSS_COMPILE = 
    CFLAGS_PLATFORM = 
endef

define set_platform_armv7l_linux_type2
    PLATFORM_DESC = LTE
    CROSS_COMPILE = /usr/local/oecore-x86_64/sysroots/x86_64-oesdk-linux/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-
    CFLAGS_PLATFORM = -march=armv7-a -mfloat-abi=softfp -mfpu=neon --sysroot=/usr/local/oecore-x86_64/sysroots/armv7a-vfp-neon-oe-linux-gnueabi
endef

define set_platform_armv7l_linux_type3
    PLATFORM_DESC = Raspberry Pi 4.19
    CROSS_COMPILE = 
    CFLAGS_PLATFORM = 
endef

define set_platform_armv7l_linux_type4
    PLATFORM_DESC = Raspberry Pi 4.9
    CROSS_COMPILE = 
    CFLAGS_PLATFORM = 
endef

define set_platform_armv7l_linux_type5
    PLATFORM_DESC = Raspberry Pi 5.10
    CROSS_COMPILE = 
    CFLAGS_PLATFORM = 
endef

define set_platform_armv7l_linux_type6
    PLATFORM_DESC = SAMA7G54-EK 5.15
    CROSS_COMPILE = ../toolchain/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
    CFLAGS_PLATFORM = 
endef

define set_platform_armv7l_linux_type7
    PLATFORM_DESC = Raspberry Pi 6.6
    CROSS_COMPILE = 
    CFLAGS_PLATFORM = 
endef

define set_platform_aarch64_linux_type1
    PLATFORM_DESC = Raspberry Pi 4.9 (64bit)
    CROSS_COMPILE = 
    CFLAGS_PLATFORM = 
endef

define set_platform_aarch64_linux_type2
    PLATFORM_DESC = Raspberry Pi 5.10 (64bit)
    CROSS_COMPILE = 
    CFLAGS_PLATFORM = 
endef

define set_platform_unknown_platform
	PLATFORM_DESC = Unknown Platform
	CROSS_COMPILE =
	CFLAGS_PLATFORM =
endef

# 플랫폼 설정 적용
$(eval $(call set_platform_$(PLATFORM)))

# 컴파일러 및 도구 설정
CC = $(CROSS_COMPILE)gcc
STRIP = $(CROSS_COMPILE)strip

# 컴파일 플래그
COMPILE_FLAGS = -O2 -fpic -fomit-frame-pointer -Wno-stringop-overflow -fcommon $(CFLAGS_PLATFORM)
CFLAGS = $(COMPILE_FLAGS) -Wall -Wextra
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

# 소스 파일 통합
ALL_SRC = $(PQCAPI_SRC) $(KEM_512_SRC) $(KEM_768_SRC) $(KEM_1024_SRC) $(DSA_44_SRC) $(DSA_65_SRC) $(DSA_87_SRC) $(COMMON_SRC)

# 목적 파일
OBJS = $(ALL_SRC:.c=.o)

# 기본 타겟 - 도움말 표시
.PHONY: default
default:
	@echo "오류: 플랫폼과 명령을 지정해주세요."
	@echo "사용 가능한 옵션을 보려면 'make help'를 실행하세요."
	@exit 1

.PHONY: all clean prepare build_all static test install pack clean_all help reset $(SUPPORTED_PLATFORMS)

# 플랫폼별 타겟 정의 - 이제 직접 빌드 실행
$(SUPPORTED_PLATFORMS):
	@$(MAKE) PLATFORM=$@ build

# 실제 빌드 실행
build:
	@echo "플랫폼 $(PLATFORM_DESC)용 $(PLATFORM) 빌드 시작..."
	@mkdir -p $(PACKAGE_DIR)
	@for src in $(ALL_SRC); do \
		echo "컴파일: $$src"; \
		$(CC) $(CFLAGS) $(INCLUDES) -c $$src -o $${src%.c}.o; \
	done
	@echo "공유 라이브러리 빌드 중..."
	$(CC) $(CFLAGS) $(LDFLAGS) -Wl,-soname,$(TARGET_SO) -o $(PACKAGE_DIR)/$(TARGET_SO) $(OBJS)
	$(STRIP) --strip-all $(PACKAGE_DIR)/$(TARGET_SO)
	chmod 644 $(PACKAGE_DIR)/$(TARGET_SO)
	@echo "✔ 빌드 완료: $(PACKAGE_DIR)/$(TARGET_SO)"
	@echo "임시 오브젝트 파일 정리 중..."
	@rm -f $(OBJS)

# 모든 플랫폼 빌드
build_all:
	@for platform in $(SUPPORTED_PLATFORMS); do \
		echo "$$platform 빌드 중..."; \
		$(MAKE) PLATFORM=$$platform $$platform; \
	done
	@echo "모든 빌드가 완료되었습니다."

# 정적 라이브러리 빌드
static:
	@if [ "$(PLATFORM)" = "unknown_platform" ]; then \
		echo "오류: 유효한 플랫폼을 지정해주세요."; \
		echo "사용 가능한 플랫폼을 보려면 'make help'를 실행하세요."; \
		exit 1; \
	fi
	@mkdir -p $(PACKAGE_DIR)
	@for src in $(ALL_SRC); do \
		echo "컴파일: $$src"; \
		$(CC) $(CFLAGS) $(INCLUDES) -c $$src -o $${src%.c}.o; \
	done
	ar rcs $(PACKAGE_DIR)/$(PACKAGE_NAME)-$(PLATFORM).a $(OBJS)
	@echo "✔ 정적 라이브러리 빌드 완료: $(PACKAGE_DIR)/$(PACKAGE_NAME)-$(PLATFORM).a"
	@rm -f $(OBJS)


# 테스트 빌드
test:
	@if [ "$(PLATFORM)" = "unknown_platform" ]; then \
		echo "오류: 유효한 플랫폼을 지정해주세요."; \
		echo "사용 가능한 플랫폼을 보려면 'make help'를 실행하세요."; \
		exit 1; \
	fi
	@mkdir -p test
	$(CC) $(CFLAGS) $(INCLUDES) -o test/test_pqcapi_$(PLATFORM) test/test_pqcapi.c -L$(PACKAGE_DIR) -l:$(TARGET_SO)
	@echo "✔ 테스트 빌드 완료: test/test_pqcapi_$(PLATFORM)"
	@echo "테스트 실행 중..."
	@LD_LIBRARY_PATH=$(PACKAGE_DIR) test/test_pqcapi_$(PLATFORM)

# 설치
install:
	@if [ "$(PLATFORM)" = "unknown_platform" ]; then \
		echo "오류: 유효한 플랫폼을 지정해주세요."; \
		echo "사용 가능한 플랫폼을 보려면 'make help'를 실행하세요."; \
		exit 1; \
	fi
	install -d $(DESTDIR)/usr/lib/$(PACKAGE_NAME)
	install -d $(DESTDIR)/usr/include/$(PACKAGE_NAME)
	install -m 755 $(PACKAGE_DIR)/$(TARGET_SO) $(DESTDIR)/usr/lib/$(PACKAGE_NAME)
	install -m 644 $(INCLUDE_DIR)/pqc_define.h $(DESTDIR)/usr/include/$(PACKAGE_NAME)
	install -m 644 $(INCLUDE_DIR)/pqc_extern.h $(DESTDIR)/usr/include/$(PACKAGE_NAME)
	ldconfig
	@echo "✔ $(PLATFORM) ($(PLATFORM_DESC)) 설치가 완료되었습니다."

# 정리
clean:
	# @if [ "$(PLATFORM)" = "unknown_platform" ]; then \
	# 	echo "오류: 유효한 플랫폼을 지정해주세요."; \
	# 	echo "사용 가능한 플랫폼을 보려면 'make help'를 실행하세요."; \
	# 	exit 1; \
	# fi
	rm -f $(OBJS)
	rm -f $(PACKAGE_DIR)/$(TARGET_SO)
	rm -f $(PACKAGE_DIR)/$(PACKAGE_NAME)-$(PLATFORM).a
	rm -f test/test_pqcapi_$(PLATFORM)
	rm -rf $(PACKAGE_DIR)/$(PACKAGE_NAME)_$(PLATFORM)
	@echo "✔ $(PLATFORM) 빌드 파일이 정리되었습니다."

# 모든 플랫폼 빌드 결과물 정리
clean_all:
	rm -f $(OBJS)
	rm -f $(PACKAGE_DIR)/$(PACKAGE_NAME)_*.so
	rm -f $(PACKAGE_DIR)/$(PACKAGE_NAME)-*.a
	rm -f test/test_pqcapi_*
	rm -rf $(PACKAGE_DIR)/$(PACKAGE_NAME)_*
	@echo "✔ 모든 빌드 파일이 정리되었습니다."

# 도움말
help:
	@echo "사용법: make [플랫폼] [옵션]"
	@echo ""
	@echo "플랫폼 목록:"
	@for p in $(SUPPORTED_PLATFORMS); do \
		$(MAKE) -s PLATFORM=$$p eval_desc; \
	done
	@echo ""
	@echo "옵션:"
	@echo "  static                정적 라이브러리 빌드"
	@echo "  test                  테스트 애플리케이션 빌드 및 실행"
	@echo "  clean                 현재 플랫폼의 빌드 파일 정리"
	@echo "  clean_all             모든 플랫폼의 빌드 파일 정리"
	@echo "  install               시스템에 라이브러리 설치"
	@echo "  build_all             모든 플랫폼 빌드"
	@echo "  help                  이 도움말 표시"
	@echo ""
	@echo "예시:"
	@echo "  make x64_linux_type2          x64_linux_type2 플랫폼용 빌드"
	@echo "  make x64_linux_type2 install  x64_linux_type2 플랫폼용 빌드 및 설치"
	@echo "  make PLATFORM=armv7l_linux_type5 pack  armv7l_linux_type5 플랫폼용 패키지 생성"

.PHONY: eval_desc
eval_desc:
	@echo "  $(PLATFORM)    $(PLATFORM_DESC)"