# MCU name
# MCU = atmega32u4

# Bootloader selection
# BOOTLOADER = qmk-dfu

# Build Options
BOOTMAGIC_ENABLE = no      	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no       	# Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight
RGB_MATRIX_ENABLE = yes		# Enable RGB Matrix light
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
TAP_DANCE_ENABLE = no		# Enable tap dance

# Oled
OLED_ENABLE = yes
OLED_DRIVER = SSD1306

# Trackball
PIMORONI_TRACKBALL_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball
SRC += drivers/sensors/pimoroni_trackball.c
QUANTUM_LIB_SRC += i2c_master.c
ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
endif

# Others
EXTRAFLAGS += -flto
# DEBOUNCE_TYPE = sym_g
# DEBOUNCE = 15
