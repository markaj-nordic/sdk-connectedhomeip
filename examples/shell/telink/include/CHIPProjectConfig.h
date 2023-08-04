/*
 *
 *    Copyright (c) 2023 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *          Example project configuration file for CHIP.
 *
 *          This is a place to put application or project-specific overrides
 *          to the default configuration values for general CHIP features.
 *
 */

#pragma once

// Use a default pairing code if one hasn't been provisioned in flash.
#define CHIP_DEVICE_CONFIG_USE_TEST_SETUP_PIN_CODE 20202021
#define CHIP_DEVICE_CONFIG_USE_TEST_SETUP_DISCRIMINATOR 0xF00

/**
 * CHIP_SYSTEM_CONFIG_PACKETBUFFER_POOL_SIZE
 *
 * Reduce packet buffer pool size to 8 (default 15) to reduce ram consumption
 */
#define CHIP_SYSTEM_CONFIG_PACKETBUFFER_POOL_SIZE 8

// Enable support functions for parsing command-line arguments
#define CHIP_CONFIG_ENABLE_ARG_PARSER 1

#define CHIP_DEVICE_CONFIG_DISABLE_SHELL_PING 1

// shell app uses openthread but does not have the NETWORK_COMMISSIONING cluster or zap config
// Do not instantiate the NETWORK_COMMISSIONING thread driver
#define _NO_NETWORK_COMMISSIONING_DRIVER_
