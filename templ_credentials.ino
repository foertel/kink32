/**
 * fill out and move this to 00_credentials.ino
 * it is .gitignored, so please don't push your tokens
 * and passwords to git. \o/
 */

 /**
 * WIFI
 */
// @todo use wifiManager
const char* ssid = "";
const char* password = "";

/**
 * Telegram
 */
// @todo use eeeprom
#define BOTtoken ""  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
// At the moment the bot supports two controlling telegram accounts.
// @todo use array to add people instead
#define CHAT_ID_1 ""
#define CHAT_ID_2 ""

/**
 * COLLAR
 */
const uint8_t  tx_pin = D1; // PIN where 433 sender is located
const uint16_t transmitter_id = 0x...; // use id you got from 'collar' script RX example