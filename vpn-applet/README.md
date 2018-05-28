# VPN-applet
VPN\Tor system tray menu applet. Make enable\disable of tor\vpn easy.

### Dependencies
- Qt5
- x-terminal-emulator
- OpenVPN (optional)
- Tor

### Build
```bash
	qmake volume-popup.pro
	make -j$(nproc)
```
move in any script folder you like

### Usage
```bash
	vpn-applet /path/to/your/ovpn/file.ovpn
```

### License
GPL v3.0
