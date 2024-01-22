#!/bin/bash

# Set the directory where the binary is installed
INSTALL_DIR="/usr/local/bin"
# Set the directory where logs are stored
LOG_DIR="/var/log/power_management"
# Set the directory where the systemd service file is located
SYSTEMD_DIR="/etc/systemd/system"
# Set the name of the systemd service
SERVICE_NAME="power_management"

# Stop and disable the systemd service
sudo systemctl stop "$SERVICE_NAME.service"
sudo systemctl disable "$SERVICE_NAME.service"

# Remove the systemd service file
sudo rm -f "$SYSTEMD_DIR/$SERVICE_NAME.service"

# Remove the binary from the installation directory
sudo rm -f "$INSTALL_DIR/power_management"

# Remove the log directory
sudo rm -rf "$LOG_DIR"

echo "Removal completed successfully."
