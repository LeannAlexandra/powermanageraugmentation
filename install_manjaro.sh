#!/bin/bash

# Set the directory where you want to install the binary
INSTALL_DIR="/usr/local/bin"
# Set the directory where you want to store logs
LOG_DIR="/var/log/power_management"
# Set the directory where you want to place the systemd service file
SYSTEMD_DIR="/etc/systemd/system"
# Set the name of the systemd service
SERVICE_NAME="power_management"

# Compile the C code
gcc -o power_management main.c -lX11 -lXss

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Move the binary to the installation directory
    sudo mv power_management "$INSTALL_DIR/"

    # Create the log directory
    sudo mkdir -p "$LOG_DIR"
    
    # Create the systemd service file
    echo "[Unit]
Description=Power Management Service
After=network.target

[Service]
ExecStart=$INSTALL_DIR/power_management
Restart=always
User=root
WorkingDirectory=$INSTALL_DIR

[Install]
WantedBy=multi-user.target" | sudo tee "$SYSTEMD_DIR/$SERVICE_NAME.service" > /dev/null

    # Enable the service to start at boot
    sudo systemctl enable "$SERVICE_NAME.service"

    # Start the service
    sudo systemctl start "$SERVICE_NAME.service"

    echo "Installation completed successfully."
else
    echo "Compilation failed. Please check your code."
fi
