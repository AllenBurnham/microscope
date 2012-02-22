/* Microscope controller for Arduino 
 * By Dustin Andrews, Frank Luecke, David Luecke and Allen Burnham, 2012
 * This work is licensed under a Creative Commons Attribution 3.0 Unported License.
 * http://creativecommons.org/licenses/by/3.0/
 * This program is design to run on Arduino MEGA
 * This program emulates the MFC-2000 ASI protocol described at http://www.asiimaging.com/ftp2asi/Manuals/MS2000%20Programming.pdf
 * Code available from https://github.com/dustinandrews/microscope
 */

#include "AsiMS2000.h"
//needs to be long enough to contain biggest command string.
#define BUFFERSIZE 128


AsiMS2000::AsiMS2000()
{
  _numCommands = NUMCOMMANDS;

}

void AsiMS2000::checkSerial()
{
  int inByte = 0;
  static int bufferPos = 0;
  static char commandBuffer [BUFFERSIZE];
  if(Serial1.available() > 0)
  {
    inByte = Serial1.read();
    int x = (int)inByte;
    char buffer [20];
    sprintf(buffer, "(%d)", x);
    Serial.print(buffer);
    Serial.print(inByte, BYTE); 
    if(bufferPos > BUFFERSIZE)
    {
      bufferPos = 0;
      bufferOverunError(commandBuffer);
      return;
    }
    
    
    //check for <CR> or | since arduino env can't send CR.
    if(inByte == 13 || inByte == 124)
    {
      Serial.println("");
      commandBuffer[bufferPos]  = '\0';
      interpretCommand(commandBuffer, bufferPos);
      bufferPos =0;
    }
    else if(inByte == 10 || inByte == 27)//backspace or escape
    {
      clearCommandBuffer(commandBuffer);
      bufferPos = 0;
    }
    else if(inByte > 31)//ignore control characters
    {
      commandBuffer[bufferPos++] = inByte;
    }
  }
}


void AsiMS2000::interpretCommand(char commandBuffer[], int bufferPos)
{
    Serial.println("interpretting");
    Serial.println(commandBuffer);
    String c = String(commandBuffer);
    int s = c.indexOf(' ');
    clearCommandBuffer(commandBuffer);
    
    String base;
    if(s > 0)
    {
      base = c.substring(0,s);
    }
    else
    {
      base = c;
    }
    
    int commandNum = getCommandNum(base);
    if(commandNum > -1)
    {
      Serial.print(c);
      Serial.print(" detected command number: ");
      Serial.println(commandNum);
      selectCommand(commandNum);
    }
}


int AsiMS2000::getCommandNum(String c)
{
  Serial.println("checking for command.");
  for(int i = 0; i < _numCommands; i++)
  {
    if( c.equalsIgnoreCase(_commands[i]) || c.equalsIgnoreCase(_shortcuts[i]) )
    {
      return i;
    }     
  }
  returnErrorToSerial(-1);//unknown command
  return -1;
}

void AsiMS2000::bufferOverunError(char commandBuffer[])
{
  returnErrorToSerial(-6);
  clearCommandBuffer(commandBuffer);
}

void AsiMS2000::clearCommandBuffer(char commandBuffer[])
{
  for(int i = 0; i < BUFFERSIZE; i++)
  {
    commandBuffer[i] = '\0';
  }
}

void AsiMS2000::displayCommands()
{
  char buffer [50];
  for(int i = 0; i < _numCommands; i++)
  {
    sprintf(buffer, "%s => %s", _commands[i], _shortcuts[i]);
    Serial.println(buffer);
  }
}


//In order to easily switch serial ports, run all data through subroutines
void AsiMS2000::serialPrint(char* data)
{
  Serial.print(">");
  Serial.println(data);
  Serial1.print(data);
}

void AsiMS2000::serialPrintln(char* data)
{
  Serial.print(">");
  Serial.println(data);
  Serial1.println(data);
}

void AsiMS2000::returnErrorToSerial(int errornum)
{
  serialPrint(":N");
  char e [1] = {errornum};
  serialPrintln(e);
}

void AsiMS2000::accel()
{
    returnErrorToSerial(-6);
}


void AsiMS2000::aalign()
{
    returnErrorToSerial(-6);
}

void AsiMS2000::afcont()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::aflim()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::afocus()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::afset()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::afmove()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::ahome()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::aij()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::array()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::azero()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::backlash()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::bcustom()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::benable()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::build()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::cdate()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::cnts()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::customa()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::customb()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::dack()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::dump()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::ensync()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::epolarity()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::error()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::halt()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::here()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::home()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::info()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::joystick()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::jsspd()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::kadc()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::kd()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::ki()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::kp()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::lcd()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::led()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::lladdr()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::load()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::lock()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::lockrg()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::lockset()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::maintain()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::motctrl()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::move()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::movrel()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::pcros()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::pedal()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::rbmode()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::rdadc()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::rdsbyte()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::rdstat()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::relock()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::reset()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::rt()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::runaway()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::saveset()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::savepos()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::scan()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::scanr()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::scanv()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::secure()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::sethome()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::setlow()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::setup()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::si()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::speed()
{
    returnErrorToSerial(-6);
}


void AsiMS2000::spin()
{
    returnErrorToSerial(-6);
}


void AsiMS2000::status()
{
    //Status should send "B" for Busy and "N" for Not busy.
    serialPrintln("N");
}


void AsiMS2000::stopbits()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::ttl()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::um()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::units()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::unlock()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::vb()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::vector()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::version()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::wait()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::where()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::who()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::wrdac()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::zero()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::z2b()
{
    returnErrorToSerial(-6);


}


void AsiMS2000::zs()
{
    returnErrorToSerial(-6);


}

void AsiMS2000::selectCommand(int commandNum)
{
  switch(commandNum)
  {
      case 0:
          accel();
          break;
      case 1:
          aalign();
          break;
      case 2:
          afcont();
          break;
      case 3:
          aflim();
          break;
      case 4:
          afocus();
          break;
      case 5:
          afset();
          break;
      case 6:
          afmove();
          break;
      case 7:
          ahome();
          break;
      case 8:
          aij();
          break;
      case 9:
          array();
          break;
      case 10:
          azero();
          break;
      case 11:
          backlash();
          break;
      case 12:
          bcustom();
          break;
      case 13:
          benable();
          break;
      case 14:
          build();
          break;
      case 15:
          cdate();
          break;
      case 16:
          cnts();
          break;
      case 17:
          customa();
          break;
      case 18:
          customb();
          break;
      case 19:
          dack();
          break;
      case 20:
          dump();
          break;
      case 21:
          ensync();
          break;
      case 22:
          epolarity();
          break;
      case 23:
          error();
          break;
      case 24:
          halt();
          break;
      case 25:
          here();
          break;
      case 26:
          home();
          break;
      case 27:
          info();
          break;
      case 28:
          joystick();
          break;
      case 29:
          jsspd();
          break;
      case 30:
          kadc();
          break;
      case 31:
          kd();
          break;
      case 32:
          ki();
          break;
      case 33:
          kp();
          break;
      case 34:
          lcd();
          break;
      case 35:
          led();
          break;
      case 36:
          lladdr();
          break;
      case 37:
          load();
          break;
      case 38:
          lock();
          break;
      case 39:
          lockrg();
          break;
      case 40:
          lockset();
          break;
      case 41:
          maintain();
          break;
      case 42:
          motctrl();
          break;
      case 43:
          move();
          break;
      case 44:
          movrel();
          break;
      case 45:
          pcros();
          break;
      case 46:
          pedal();
          break;
      case 47:
          rbmode();
          break;
      case 48:
          rdadc();
          break;
      case 49:
          rdsbyte();
          break;
      case 50:
          rdstat();
          break;
      case 51:
          relock();
          break;
      case 52:
          reset();
          break;
      case 53:
          rt();
          break;
      case 54:
          runaway();
          break;
      case 55:
          saveset();
          break;
      case 56:
          savepos();
          break;
      case 57:
          scan();
          break;
      case 58:
          scanr();
          break;
      case 59:
          scanv();
          break;
      case 60:
          secure();
          break;
      case 61:
          sethome();
          break;
      case 62:
          setlow();
          break;
      case 63:
          setup();
          break;
      case 64:
          si();
          break;
      case 65:
          speed();
          break;
      case 66:
          spin();
          break;
      case 67:
          status();
          break;
      case 68:
          stopbits();
          break;
      case 69:
          ttl();
          break;
      case 70:
          um();
          break;
      case 71:
          units();
          break;
      case 72:
          unlock();
          break;
      case 73:
          vb();
          break;
      case 74:
          vector();
          break;
      case 75:
          version();
          break;
      case 76:
          wait();
          break;
      case 77:
          where();
          break;
      case 78:
          who();
          break;
      case 79:
          wrdac();
          break;
      case 80:
          zero();
          break;
      case 81:
          z2b();
          break;
      case 82:
          zs();
          break;

  }
}


char*  AsiMS2000::_commands[] =
        {"ACCEL","AALIGN","AFCONT","AFLIM","AFOCUS","AFSET","AFMOVE",
                  "AHOME","AIJ","ARRAY","AZERO","BACKLASH","BCUSTOM","BENABLE","BUILD",
                  "CDATE","CNTS","CUSTOMA","CUSTOMB","DACK","DUMP","ENSYNC","EPOLARITY",
                  "ERROR","HALT","HERE","HOME","INFO","JOYSTICK","JSSPD","KADC","KD","KI",
                  "KP","LCD","LED","LLADDR","LOAD","LOCK","LOCKRG","LOCKSET","MAINTAIN",
                  "MOTCTRL","MOVE","MOVREL","PCROS","PEDAL","RBMODE","RDADC","RDSBYTE",
                  "RDSTAT","RELOCK","RESET","RT","RUNAWAY","SAVESET","SAVEPOS","SCAN",
                  "SCANR","SCANV","SECURE","SETHOME","SETLOW","SETUP","SI","SPEED","SPIN",
                  "STATUS","STOPBITS","TTL","UM","UNITS","UNLOCK","VB","VECTOR","VERSION",
                  "WAIT","WHERE","WHO","WRDAC","ZERO","Z2B","ZS"
                  };
                  
char* AsiMS2000::_shortcuts[] =
        {"AC","AA","AFCONT","AFLIM","AFOCUS","AFSET","AFMOVE",
                   "AH","IJ","AR","AZ","B","BCA","BE","BU",
                   "CD","C","CCA","CCB","D","DU","ES","EP",
                   "E","\\","H","!","I","J","JS","KA","KD","KI",
                   "KP","LCD","LED","LL","LD","LK","LR","LS","MA",
                   "MC","M","R","PC","PD","RM","RA","RB",
                   "RS","RL","~","RT","RU","SS","SP","SN",
                   "NR","NV","SECURE","HM","SL","SU","SI","S","@",
                   "/","SB","TTL","UM","UN","UL","VB","VE","V",
                   "WT","W","N","WRDAC","Z","Z2B","ZS"
                   };

