#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 500;
unsigned long lastTimeBotRan;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    // @todo use an array instead, this looks ugly
    if (chat_id != CHAT_ID_1 && chat_id != CHAT_ID_2){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    if (bot.messages[i].type == "callback_query")
    {
      String callbackData = bot.messages[i].text;

      Serial.print("Call back button pressed by: ");
      Serial.println(bot.messages[i].from_id);

      if (callbackData.startsWith("vibrate-")) {
        char commandLine[callbackData.length() + 1];
        
        callbackData.toCharArray(commandLine, callbackData.length() + 1);
        Serial.println(commandLine);

        char* command = strtok(commandLine, "-");
        
        // pop the command
        command = strtok(NULL, "-");
        int vibrateLevel = atoi(command);

        send_vibrate(vibrateLevel);
          String message = "Daddy wurde auf Stufe ";
          message += vibrateLevel;
          message += " geschüttelt.";
          bot.sendMessage(chat_id, message, "");
      } else if (callbackData.startsWith("shock-")) {
        char commandLine[callbackData.length() + 1];
        
        callbackData.toCharArray(commandLine, callbackData.length() + 1);
        Serial.println(commandLine);

        char* command = strtok(commandLine, "-");
        
        // pop the command
        command = strtok(NULL, "-");
        int shockLevel = atoi(command);

        send_shock(shockLevel);
          String message = "Daddy wurde auf Stufe ";
          message += shockLevel;
          message += " geschockt.";
          bot.sendMessage(chat_id, message, "");
      }       
    } else {
      // Print the received message
      String text = bot.messages[i].text;
      Serial.println(text);

      String from_name = bot.messages[i].from_name;

      if (text == "/start") {
        String welcome = "Willkommen, " + from_name + ".\n";
        bot.sendMessage(chat_id, welcome, "");
      }

      /**
       * SET VIBRATION
       */
      if (text.startsWith("/setvibrate")) {
        char commandLine[text.length() + 1];
        
        text.toCharArray(commandLine, text.length() + 1);
        Serial.println(commandLine);

        char* command = strtok(commandLine, " ,");
        
          // pop the command
          command = strtok(NULL, " ,");

          memset(vibrateLevels, 0, sizeof(vibrateLevels));
          int vibrateLevelIndex = 0;
          
          while (command != NULL) {
            Serial.println("Setting parameter: ");
            Serial.print(command);
            vibrateLevels[vibrateLevelIndex++] = atoi(command);
            command = strtok(NULL, " ,");
          }

          bot.sendMessage(chat_id, "Deine neuen Vibrationslevel wurden gespeichert.", "");
      }

      /**
       * SET SHOCKS
       */
      if (text.startsWith("/setshock")) {
        char commandLine[text.length() + 1];
        
        text.toCharArray(commandLine, text.length() + 1);
        Serial.println(commandLine);

        char* command = strtok(commandLine, " ,");
        
          // pop the command
          command = strtok(NULL, " ,");

          memset(shockLevels, 0, sizeof(shockLevels));
          int shockLevelIndex = 0;
          
          while (command != NULL) {
            Serial.println("Setting parameter: ");
            Serial.print(command);
            shockLevels[shockLevelIndex++] = atoi(command);
            command = strtok(NULL, " ,");
          }

          bot.sendMessage(chat_id, "Deine neuen Schocklevel wurden gespeichert.", "");
      }

      /**
       * VIBRATE
       */
      if (text.startsWith("/vibrate")) {
        int vibLevelCount = 0;
        for (int j = 0; j < sizeof(vibrateLevels) / sizeof(int); j++) {
          Serial.println("count j:");
          Serial.println(j);
          Serial.println("level value:");
          Serial.println(vibrateLevels[j]);
          if (vibrateLevels[j] > 0) {
            vibLevelCount++;
          }
        }

        Serial.println("VibLevelCount:");
        Serial.println(vibLevelCount);

        String keyboardJson = "";

        if (vibLevelCount > 1) {
          keyboardJson = "[";
          for (int j = 0; j < vibLevelCount; j++) {
            keyboardJson += "[{ \"text\" : \"";
            keyboardJson += vibrateLevels[j];
            keyboardJson += "\", \"callback_data\" : \"vibrate-";
            keyboardJson += vibrateLevels[j];
            keyboardJson += "\" }]";

            if (j < vibLevelCount - 1) {
              keyboardJson += ",";
            }
          }
          keyboardJson += "]";
          bot.sendMessageWithInlineKeyboard(chat_id, "Wähle eine Stufe, um Daddy zu schütteln.", "", keyboardJson);
        } else {
          int level = vibrateLevels[0];
          send_vibrate(level);
          String message = "Daddy wurde auf Stufe ";
          message += level;
          message += " geschüttelt.";
          bot.sendMessage(chat_id, message, "");
        }
      
      /**
     * SHOCK
     */
      } else if (text.startsWith("/shock")) {
        int shockLevelCount = 0;
        for (int j = 0; j < sizeof(shockLevels) / sizeof(int); j++) {
          Serial.println("count j:");
          Serial.println(j);
          Serial.println("level value:");
          Serial.println(shockLevels[j]);
          if (shockLevels[j] > 0) {
            shockLevelCount++;
          }
        }

        Serial.println("shockLevelCount:");
        Serial.println(shockLevelCount);

        String keyboardJson = "";

        if (shockLevelCount > 1) {
          keyboardJson = "[";
          for (int j = 0; j < shockLevelCount; j++) {
            keyboardJson += "[{ \"text\" : \"";
            keyboardJson += shockLevels[j];
            keyboardJson += "\", \"callback_data\" : \"shock-";
            keyboardJson += shockLevels[j];
            keyboardJson += "\" }]";

            if (j < shockLevelCount - 1) {
              keyboardJson += ",";
            }
          }
          keyboardJson += "]";
          bot.sendMessageWithInlineKeyboard(chat_id, "Wähle eine Stufe, um Daddy zu shocken.", "", keyboardJson);
        } else {
          int level = shockLevels[0];
          send_shock(level);
          String message = "Daddy wurde auf Stufe ";
          message += level;
          message += " geschockt.";
          bot.sendMessage(chat_id, message, "");
        }
      }
    }
  }
}