/*
 * Automatically generated file. DO NOT EDIT.
 * Espressif IoT Development Framework (ESP-IDF) Configuration Header
 */
#pragma once
#define CONFIG_IDF_CMAKE 1
#define CONFIG_IDF_TARGET_ARCH_RISCV 1
#define CONFIG_IDF_TARGET "esp32c3"
#define CONFIG_IDF_TARGET_ESP32C3 1
#define CONFIG_IDF_FIRMWARE_CHIP_ID 0x0005
#define CONFIG_SDK_TOOLPREFIX "riscv32-esp-elf-"
#define CONFIG_APP_BUILD_TYPE_APP_2NDBOOT 1
#define CONFIG_APP_BUILD_GENERATE_BINARIES 1
#define CONFIG_APP_BUILD_BOOTLOADER 1
#define CONFIG_APP_BUILD_USE_FLASH_SECTIONS 1
#define CONFIG_BOOTLOADER_OFFSET_IN_FLASH 0x0
#define CONFIG_BOOTLOADER_COMPILER_OPTIMIZATION_SIZE 1
#define CONFIG_BOOTLOADER_LOG_LEVEL_INFO 1
#define CONFIG_BOOTLOADER_LOG_LEVEL 3
#define CONFIG_BOOTLOADER_VDDSDIO_BOOST_1_9V 1
#define CONFIG_BOOTLOADER_WDT_ENABLE 1
#define CONFIG_BOOTLOADER_WDT_TIME_MS 9000
#define CONFIG_BOOTLOADER_RESERVE_RTC_SIZE 0x0
#define CONFIG_BOOTLOADER_FLASH_XMC_SUPPORT 1
#define CONFIG_SECURE_BOOT_SUPPORTS_RSA 1
#define CONFIG_SECURE_TARGET_HAS_SECURE_ROM_DL_MODE 1
#define CONFIG_BOOT_ROM_LOG_ALWAYS_ON 1
#define CONFIG_ESPTOOLPY_BAUD_OTHER_VAL 115200
#define CONFIG_ESPTOOLPY_FLASHMODE_DIO 1
#define CONFIG_ESPTOOLPY_FLASH_SAMPLE_MODE_STR 1
#define CONFIG_ESPTOOLPY_FLASHMODE "dio"
#define CONFIG_ESPTOOLPY_FLASHFREQ_80M 1
#define CONFIG_ESPTOOLPY_FLASHFREQ "80m"
#define CONFIG_ESPTOOLPY_FLASHSIZE_4MB 1
#define CONFIG_ESPTOOLPY_FLASHSIZE "4MB"
#define CONFIG_ESPTOOLPY_FLASHSIZE_DETECT 1
#define CONFIG_ESPTOOLPY_BEFORE_RESET 1
#define CONFIG_ESPTOOLPY_BEFORE "default_reset"
#define CONFIG_ESPTOOLPY_AFTER_RESET 1
#define CONFIG_ESPTOOLPY_AFTER "hard_reset"
#define CONFIG_ESPTOOLPY_MONITOR_BAUD_115200B 1
#define CONFIG_ESPTOOLPY_MONITOR_BAUD_OTHER_VAL 115200
#define CONFIG_ESPTOOLPY_MONITOR_BAUD 115200
#define CONFIG_PARTITION_TABLE_SINGLE_APP 1
#define CONFIG_PARTITION_TABLE_CUSTOM_FILENAME "partitions.csv"
#define CONFIG_PARTITION_TABLE_FILENAME "partitions_singleapp.csv"
#define CONFIG_PARTITION_TABLE_OFFSET 0x8000
#define CONFIG_PARTITION_TABLE_MD5 1
#define CONFIG_COMPILER_OPTIMIZATION_DEFAULT 1
#define CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_ENABLE 1
#define CONFIG_COMPILER_OPTIMIZATION_ASSERTION_LEVEL 2
#define CONFIG_COMPILER_HIDE_PATHS_MACROS 1
#define CONFIG_COMPILER_STACK_CHECK_MODE_NONE 1
#define CONFIG_EFUSE_MAX_BLK_LEN 256
#define CONFIG_ESP32C3_DEFAULT_CPU_FREQ_160 1
#define CONFIG_ESP32C3_DEFAULT_CPU_FREQ_MHZ 160
#define CONFIG_ESP32C3_REV_MIN_3 1
#define CONFIG_ESP32C3_REV_MIN 3
#define CONFIG_ESP32C3_DEBUG_OCDAWARE 1
#define CONFIG_ESP32C3_BROWNOUT_DET 1
#define CONFIG_ESP32C3_BROWNOUT_DET_LVL_SEL_7 1
#define CONFIG_ESP32C3_BROWNOUT_DET_LVL 7
#define CONFIG_ESP32C3_TIME_SYSCALL_USE_RTC_SYSTIMER 1
#define CONFIG_ESP32C3_RTC_CLK_SRC_INT_RC 1
#define CONFIG_ESP32C3_RTC_CLK_CAL_CYCLES 1024
#define CONFIG_ESP_ERR_TO_NAME_LOOKUP 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_WIFI_STA 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_WIFI_AP 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_BT 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_ETH 1
#define CONFIG_ESP32C3_UNIVERSAL_MAC_ADDRESSES_FOUR 1
#define CONFIG_ESP32C3_UNIVERSAL_MAC_ADDRESSES 4
#define CONFIG_ESP_SLEEP_POWER_DOWN_FLASH 1
#define CONFIG_ESP_SLEEP_GPIO_RESET_WORKAROUND 1
#define CONFIG_ESP_SYSTEM_PANIC_PRINT_REBOOT 1
#define CONFIG_ESP_SYSTEM_SINGLE_CORE_MODE 1
#define CONFIG_ESP_SYSTEM_RTC_FAST_MEM_AS_HEAP_DEPCHECK 1
#define CONFIG_ESP_SYSTEM_ALLOW_RTC_FAST_MEM_AS_HEAP 1
#define CONFIG_ESP_SYSTEM_MEMPROT_DEPCHECK 1
#define CONFIG_ESP_SYSTEM_MEMPROT_FEATURE 1
#define CONFIG_ESP_SYSTEM_MEMPROT_FEATURE_LOCK 1
#define CONFIG_ESP_SYSTEM_MEMPROT_CPU_PREFETCH_PAD_SIZE 16
#define CONFIG_ESP_SYSTEM_MEMPROT_MEM_ALIGN_SIZE 512
#define CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE 32
#define CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE 2304
#define CONFIG_ESP_MAIN_TASK_STACK_SIZE 3584
#define CONFIG_ESP_MAIN_TASK_AFFINITY_CPU0 1
#define CONFIG_ESP_MAIN_TASK_AFFINITY 0x0
#define CONFIG_ESP_MINIMAL_SHARED_STACK_SIZE 2048
#define CONFIG_ESP_CONSOLE_UART_DEFAULT 1
#define CONFIG_ESP_CONSOLE_SECONDARY_USB_SERIAL_JTAG 1
#define CONFIG_ESP_CONSOLE_UART 1
#define CONFIG_ESP_CONSOLE_UART_NUM 0
#define CONFIG_ESP_CONSOLE_UART_BAUDRATE 115200
#define CONFIG_ESP_INT_WDT 1
#define CONFIG_ESP_INT_WDT_TIMEOUT_MS 300
#define CONFIG_ESP_TASK_WDT 1
#define CONFIG_ESP_TASK_WDT_TIMEOUT_S 5
#define CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0 1
#define CONFIG_ESP_SYSTEM_CHECK_INT_LEVEL_4 1
#define CONFIG_FREERTOS_UNICORE 1
#define CONFIG_FREERTOS_NO_AFFINITY 0x7FFFFFFF
#define CONFIG_FREERTOS_TICK_SUPPORT_SYSTIMER 1
#define CONFIG_FREERTOS_CORETIMER_SYSTIMER_LVL1 1
#define CONFIG_FREERTOS_SYSTICK_USES_SYSTIMER 1
#define CONFIG_FREERTOS_OPTIMIZED_SCHEDULER 1
#define CONFIG_FREERTOS_HZ 100
#define CONFIG_FREERTOS_ASSERT_ON_UNTESTED_FUNCTION 1
#define CONFIG_FREERTOS_CHECK_STACKOVERFLOW_CANARY 1
#define CONFIG_FREERTOS_INTERRUPT_BACKTRACE 1
#define CONFIG_FREERTOS_THREAD_LOCAL_STORAGE_POINTERS 1
#define CONFIG_FREERTOS_ASSERT_FAIL_ABORT 1
#define CONFIG_FREERTOS_IDLE_TASK_STACKSIZE 1536
#define CONFIG_FREERTOS_ISR_STACKSIZE 1536
#define CONFIG_FREERTOS_MAX_TASK_NAME_LEN 16
#define CONFIG_FREERTOS_SUPPORT_STATIC_ALLOCATION 1
#define CONFIG_FREERTOS_TIMER_TASK_PRIORITY 1
#define CONFIG_FREERTOS_TIMER_TASK_STACK_DEPTH 2048
#define CONFIG_FREERTOS_TIMER_QUEUE_LENGTH 10
#define CONFIG_FREERTOS_QUEUE_REGISTRY_SIZE 0
#define CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER 1
#define CONFIG_FREERTOS_CHECK_MUTEX_GIVEN_BY_OWNER 1
#define CONFIG_FREERTOS_DEBUG_OCDAWARE 1
#define CONFIG_FREERTOS_ENABLE_TASK_SNAPSHOT 1
#define CONFIG_HAL_ASSERTION_EQUALS_SYSTEM 1
#define CONFIG_HAL_DEFAULT_ASSERTION_LEVEL 2
#define CONFIG_LOG_DEFAULT_LEVEL_INFO 1
#define CONFIG_LOG_DEFAULT_LEVEL 3
#define CONFIG_LOG_MAXIMUM_EQUALS_DEFAULT 1
#define CONFIG_LOG_MAXIMUM_LEVEL 3
#define CONFIG_LOG_COLORS 1
#define CONFIG_LOG_TIMESTAMP_SOURCE_RTOS 1
#define CONFIG_NEWLIB_STDOUT_LINE_ENDING_CRLF 1
#define CONFIG_NEWLIB_STDIN_LINE_ENDING_CR 1
#define CONFIG_SPI_FLASH_ROM_DRIVER_PATCH 1
#define CONFIG_SPI_FLASH_DANGEROUS_WRITE_ABORTS 1
#define CONFIG_SPI_FLASH_YIELD_DURING_ERASE 1
#define CONFIG_SPI_FLASH_ERASE_YIELD_DURATION_MS 20
#define CONFIG_SPI_FLASH_ERASE_YIELD_TICKS 1
#define CONFIG_SPI_FLASH_WRITE_CHUNK_SIZE 8192
#define CONFIG_SPI_FLASH_SUPPORT_ISSI_CHIP 1
#define CONFIG_SPI_FLASH_SUPPORT_MXIC_CHIP 1
#define CONFIG_SPI_FLASH_SUPPORT_GD_CHIP 1
#define CONFIG_SPI_FLASH_SUPPORT_WINBOND_CHIP 1
#define CONFIG_SPI_FLASH_SUPPORT_BOYA_CHIP 1
#define CONFIG_SPI_FLASH_ENABLE_ENCRYPTED_READ_WRITE 1

/* List of deprecated options */
#define CONFIG_COMPILER_OPTIMIZATION_LEVEL_DEBUG CONFIG_COMPILER_OPTIMIZATION_DEFAULT
#define CONFIG_CONSOLE_UART_DEFAULT CONFIG_ESP_CONSOLE_UART_DEFAULT
#define CONFIG_ESP32C3_LIGHTSLEEP_GPIO_RESET_WORKAROUND CONFIG_ESP_SLEEP_GPIO_RESET_WORKAROUND
#define CONFIG_ESP32C3_MEMPROT_FEATURE CONFIG_ESP_SYSTEM_MEMPROT_FEATURE
#define CONFIG_ESP32C3_MEMPROT_FEATURE_LOCK CONFIG_ESP_SYSTEM_MEMPROT_FEATURE_LOCK
#define CONFIG_ESP32H2_MEMPROT_FEATURE CONFIG_ESP_SYSTEM_MEMPROT_FEATURE
#define CONFIG_ESP32H2_MEMPROT_FEATURE_LOCK CONFIG_ESP_SYSTEM_MEMPROT_FEATURE_LOCK
#define CONFIG_ESP32S2_ALLOW_RTC_FAST_MEM_AS_HEAP CONFIG_ESP_SYSTEM_ALLOW_RTC_FAST_MEM_AS_HEAP
#define CONFIG_ESP32S2_MEMPROT_FEATURE CONFIG_ESP_SYSTEM_MEMPROT_FEATURE
#define CONFIG_ESP32S2_MEMPROT_FEATURE_LOCK CONFIG_ESP_SYSTEM_MEMPROT_FEATURE_LOCK
#define CONFIG_ESP32S2_PANIC_PRINT_REBOOT CONFIG_ESP_SYSTEM_PANIC_PRINT_REBOOT
#define CONFIG_ESP32_ALLOW_RTC_FAST_MEM_AS_HEAP CONFIG_ESP_SYSTEM_ALLOW_RTC_FAST_MEM_AS_HEAP
#define CONFIG_ESP32_PANIC_PRINT_REBOOT CONFIG_ESP_SYSTEM_PANIC_PRINT_REBOOT
#define CONFIG_ESP_SYSTEM_PD_FLASH CONFIG_ESP_SLEEP_POWER_DOWN_FLASH
#define CONFIG_FLASHMODE_DIO CONFIG_ESPTOOLPY_FLASHMODE_DIO
#define CONFIG_INT_WDT CONFIG_ESP_INT_WDT
#define CONFIG_INT_WDT_TIMEOUT_MS CONFIG_ESP_INT_WDT_TIMEOUT_MS
#define CONFIG_LOG_BOOTLOADER_LEVEL_INFO CONFIG_BOOTLOADER_LOG_LEVEL_INFO
#define CONFIG_MAIN_TASK_STACK_SIZE CONFIG_ESP_MAIN_TASK_STACK_SIZE
#define CONFIG_MONITOR_BAUD_115200B CONFIG_ESPTOOLPY_MONITOR_BAUD_115200B
#define CONFIG_OPTIMIZATION_ASSERTIONS_ENABLED CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_ENABLE
#define CONFIG_OPTIMIZATION_LEVEL_DEBUG CONFIG_COMPILER_OPTIMIZATION_DEFAULT
#define CONFIG_SPI_FLASH_WRITING_DANGEROUS_REGIONS_ABORTS CONFIG_SPI_FLASH_DANGEROUS_WRITE_ABORTS
#define CONFIG_STACK_CHECK_NONE CONFIG_COMPILER_STACK_CHECK_MODE_NONE
#define CONFIG_SYSTEM_EVENT_QUEUE_SIZE CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE
#define CONFIG_SYSTEM_EVENT_TASK_STACK_SIZE CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE
#define CONFIG_TASK_WDT CONFIG_ESP_TASK_WDT
#define CONFIG_TASK_WDT_CHECK_IDLE_TASK_CPU0 CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
#define CONFIG_TASK_WDT_TIMEOUT_S CONFIG_ESP_TASK_WDT_TIMEOUT_S
#define CONFIG_TIMER_QUEUE_LENGTH CONFIG_FREERTOS_TIMER_QUEUE_LENGTH
#define CONFIG_TIMER_TASK_PRIORITY CONFIG_FREERTOS_TIMER_TASK_PRIORITY
#define CONFIG_TIMER_TASK_STACK_DEPTH CONFIG_FREERTOS_TIMER_TASK_STACK_DEPTH
#define CONFIG_TOOLPREFIX CONFIG_SDK_TOOLPREFIX
