#!/usr/bin/env bash
#
# Builds all 3 3dapter (Triple Controller) firmware variants with
# arduino-cli and collects the resulting .hex files in dist/. Used by both
# CI (.github/workflows/build-firmware.yml, deploy-flasher.yml) and local
# development — run this after any firmware change to confirm every build
# target still compiles.
#
# Requires: arduino-cli on PATH (e.g. `brew install arduino-cli`).
#
# --clean is used on every build below so arduino-cli's build cache can
# never silently reuse a stale core object file compiled before a
# --build-property change — see 4dapter's ci/build-all.sh for the class of
# bug this specifically guards against (a --build-property change not
# taking effect locally, only surfacing on a genuinely clean build).

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

LUFA_URL="https://github.com/CrazyRedMachine/Arduino-Lufa/raw/master/package_arduino-lufa_index.json"
XINPUT_URL="https://raw.githubusercontent.com/dmadison/ArduinoXInput_Boards/master/package_dmadison_xinput_index.json"

echo "==> Installing board cores and libraries"
arduino-cli core update-index
arduino-cli core install arduino:avr

arduino-cli core update-index --additional-urls "$LUFA_URL"
arduino-cli core install Arduino-LUFA:avr --additional-urls "$LUFA_URL"

arduino-cli core update-index --additional-urls "$XINPUT_URL"
arduino-cli core install xinput:avr --additional-urls "$XINPUT_URL"
arduino-cli lib install XInput

mkdir -p build dist
rm -f dist/*.hex

echo "==> Building 3dapter-hid"
arduino-cli compile \
  --fqbn arduino:avr:leonardo \
  --library ./lib/3dapterCore \
  --build-property 'build.usb_product="3DAPTER HID"' \
  --clean \
  --output-dir build/3dapter-hid \
  3dapter_FW-HID
cp build/3dapter-hid/3dapter_FW-HID.ino.hex dist/3dapter-hid.hex

echo "==> Building 3dapter-switch"
arduino-cli compile --fqbn Arduino-LUFA:avr:leonardo --library ./lib/3dapterCore \
  --clean \
  --output-dir build/3dapter-switch 3dapter_FW-Switch
cp build/3dapter-switch/3dapter_FW-Switch.ino.hex dist/3dapter-switch.hex

echo "==> Building 3dapter-xinput"
# The xinput:avr core's boards.txt hardcodes build.usb_product="Arduino Leonardo"
# (it's a repurposed stock Leonardo board profile) — override it so the device
# reports as "3DAPTER XInput" instead of "Arduino Leonardo" while still
# spoofing an Xbox 360 controller's VID/PID for XInput compatibility.
arduino-cli compile --fqbn xinput:avr:leonardo --library ./lib/3dapterCore \
  --build-property 'build.usb_product="3DAPTER XInput"' \
  --clean \
  --output-dir build/3dapter-xinput 3dapter_FW-XInput
cp build/3dapter-xinput/3dapter_FW-XInput.ino.hex dist/3dapter-xinput.hex

echo "==> Done. Artifacts in dist/:"
ls -la dist/
