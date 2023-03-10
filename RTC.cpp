#ifndef RTC
#define RTC

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdio.h>
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c "
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


namespace RTC {
    #define SPI_INTERFACE spi0
    #define SPI_MISO 0
    #define SPI_CS  1
    #define SPI_CLK  2
    #define SPI_MOSI 3
    //10001011
    #define COMMAND_WRITE_SECONDS 0x80
    #define COMMAND_READ_SECONDS 0x81
    #define COMMAND_WRITE_MINUTES 0x82
    #define COMMAND_READ_MINUTES 0x83

    #define COMMAND_WRITE_HOURS 0x84
    #define COMMAND_READ_HOURS 0x85
    #define COMMAND_WRITE_DAY 0x86
    #define COMMAND_READ_DAY 0x87
    #define COMMAND_WRITE_MONTH 0x88
    #define COMMAND_READ_MONTH 0x89
    #define COMMAND_WRITE_WEEKDAY 0x8A
    #define COMMAND_READ_WEEKDAY 0x8B
    #define COMMAND_WRITE_YEARS 0x8C
    #define COMMAND_READ_YEARS 0x8D

    void setMinutes(uint8_t minutes);
    uint8_t getMinutes();

    void setSeconds(uint8_t seconds);
    uint8_t getSeconds();

    void setHours(uint8_t hours);
    uint8_t getHours();

    void setDays(uint8_t Days); //todo
    uint8_t getDays(); //todo

    void setMonth(uint8_t Month);
    uint8_t getMonth();

    void setYear(unsigned int Year);
    unsigned int getYear();

    void commandStart();
    void commandEnd();
    uint8_t revertBits(uint8_t byte);
    uint8_t CommandRegister(uint8_t Register, uint8_t value = 0);
    void pauseClock();
    void startClock();
    void init();

    unsigned int binYearToDec(unsigned int binData);
    uint8_t binMonthToDec(uint8_t binData);
    uint8_t binDayToDec(uint8_t binData);
    uint8_t binHourToDec(uint8_t binData);
    uint8_t binSecMinToDec(uint8_t binData);
    unsigned int binDecToDecUni(unsigned int binData, uint8_t shift);

    unsigned int decYearToBin(unsigned int decData);
    uint8_t decMonthToBin(uint8_t decData);
    uint8_t decDayToBin(uint8_t decData); 
    uint8_t decHoursToBin(uint8_t decData);
    uint8_t decSecMinToBin(uint8_t decData);
    unsigned int decToBinDec(unsigned int decData);

    void test() {


        printf("SECONDS: %i\n",getDays());
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(CommandRegister(COMMAND_READ_YEARS)));


        printf("SECONDS: %i\n", getDays());
        sleep_ms(1000);

    }

    void test2() {
        setYear(23);
        setMonth(02);
        setDays(04);
        setHours(9);
        setMinutes(01);
        setSeconds(20);
    }



    void test3() {
        printf("%i, %i, %i, %i, %i, %i\n", getSeconds(), getMinutes(), getHours(), getDays(), getMonth(), getYear());
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(CommandRegister(COMMAND_READ_YEARS)));
        printf("\n");
        return;
        uint8_t data = CommandRegister(COMMAND_READ_HOURS);
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(data));
        printf("\n");


        return;
        
        data = CommandRegister(COMMAND_READ_HOURS);
        printf("dataRaw: %i, dataProcessed %i, databin: ", data, binSecMinToDec(data));       
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(data));
        printf("\n");



        // uint8_t seconds = CommandRegister(COMMAND_READ_SECONDS), minutes = CommandRegister(COMMAND_READ_MINUTES);
        // printf("Seconds: %i ", binSecondsToDec(seconds));       
        // printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(seconds));
        // printf(" Minutes: %i ", binSecondsToDec(minutes));
        // printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(minutes));
        // printf("\n");
        sleep_ms(999);
    }

    void test4() {
        printf("\ncleared\n");
        CommandRegister(COMMAND_WRITE_MINUTES, 0);
    }

    void setYear(unsigned int Year) {
        CommandRegister(COMMAND_WRITE_YEARS, revertBits(decYearToBin(Year)));
    }

    unsigned int getYear() {
        unsigned int data = CommandRegister(COMMAND_READ_YEARS);
        data = binYearToDec(data);
        return data;
    }

    void setMonth(uint8_t Month) {
        CommandRegister(COMMAND_WRITE_MONTH, revertBits(decMonthToBin(Month)));
    }
    
    uint8_t getMonth() {
        uint8_t data = CommandRegister(COMMAND_READ_MONTH);
        data = binMonthToDec(data);
        return data;
    }

    void setDays(uint8_t Days) {
        CommandRegister(COMMAND_WRITE_DAY, revertBits(decDayToBin(Days)));
    }

    uint8_t getDays() {
        uint8_t data = CommandRegister(COMMAND_READ_DAY);
        data = binDayToDec(data);
        return data;
    }

    void setHours(uint8_t hours) {
        CommandRegister(COMMAND_WRITE_HOURS, revertBits(decHoursToBin(hours)));
    }

    uint8_t getHours() {
        uint8_t data = CommandRegister(COMMAND_READ_HOURS);
        data = binHourToDec(data);
        return data;
    }

    void setMinutes(uint8_t minutes) {
        CommandRegister(COMMAND_WRITE_MINUTES, revertBits(decSecMinToBin(minutes)));
    }

    uint8_t getMinutes() {
        uint8_t data = CommandRegister(COMMAND_READ_MINUTES);
        data = binSecMinToDec(data);
        return data;
    }

    void setSeconds(uint8_t seconds) {
        uint8_t ch = (CommandRegister(COMMAND_READ_SECONDS) >> 0) & 1U;
        CommandRegister(COMMAND_WRITE_SECONDS, revertBits(decSecMinToBin(seconds)) | ch);
    }

    uint8_t getSeconds() {
        uint8_t data = CommandRegister(COMMAND_READ_SECONDS);
        data &= ~(1UL << 0);
        data = binSecMinToDec(data);
        return data;
    }

    void commandStart() {
        gpio_put(SPI_CS, 1);
    }
    //1 2 4 8
    //1001'1010
    void commandEnd() {
        gpio_put(SPI_CS, 0);
    }

    uint8_t revertBits(uint8_t byte) {
        uint8_t anws {0b0000'0000};
        (byte & 0x80 ? anws |=  0b0000'0001 : '0');
        (byte & 0x40 ? anws |=  0b0000'0010 : '0'); 
        (byte & 0x20 ? anws |=  0b0000'0100 : '0'); 
        (byte & 0x10 ? anws |=  0b0000'1000 : '0'); 
        (byte & 0x08 ? anws |=  0b0001'0000 : '0'); 
        (byte & 0x04 ? anws |=  0b0010'0000 : '0'); 
        (byte & 0x02 ? anws |=  0b0100'0000 : '0'); 
        (byte & 0x01 ? anws |=  0b1000'0000 : '0');
        return anws;
    }
    
    uint8_t CommandRegister(uint8_t Register, uint8_t value) {
        uint8_t input[2] {revertBits(Register), value};
        uint8_t output[2];
        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, input, output, 2);
        commandEnd();

        return output[1];
    }

    void pauseClock() {
        uint8_t input[2];
        uint8_t output[2];
        input[0] = 0b0000'0001;
        input[1] = CommandRegister(COMMAND_READ_SECONDS);
        input[1] |= 1UL << 0;
        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, input, output, 2);
        commandEnd();
    }

    void startClock() {
        uint8_t input[2];
        uint8_t output[2];
        input[0] = 0b0000'0001;
        input[1] = CommandRegister(COMMAND_READ_SECONDS);
        input[1] &= ~(1UL << 0);
        commandStart();
        spi_write_read_blocking(SPI_INTERFACE, input, output, 2);
        commandEnd();
    }

    void init() {
        //SPI
        spi_init(SPI_INTERFACE, 1*1000*1000);

        gpio_set_function(SPI_MOSI,  GPIO_FUNC_SPI);
        gpio_set_function(SPI_MISO,  GPIO_FUNC_SPI);
        gpio_set_function(SPI_CLK,   GPIO_FUNC_SPI);

        //OUT
        gpio_init(SPI_CS);
        gpio_set_dir(SPI_CS, GPIO_OUT);
        gpio_put(SPI_CS, 0);

        startClock();
    }
    //1 2 4 8 16 32 64

    uint8_t decSecMinToBin(uint8_t decData) {
        if (decData > 59) return 0;
        return decToBinDec(decData);
    }

    uint8_t decHoursToBin(uint8_t decData) {
        if (decData > 23) return 0;
        return decToBinDec(decData);
    }

    uint8_t decDayToBin(uint8_t decData) {
        if (decData > 31) return 0;
        return decToBinDec(decData);
    }

    uint8_t decMonthToBin(uint8_t decData) {
        if (decData > 12) return 0;
        return decToBinDec(decData);
    }
    unsigned int decYearToBin(unsigned int decData) {
        if (decData > 2100) return 0;
        return decToBinDec(decData);
    }

    unsigned int decToBinDec(unsigned int decData) {
        unsigned int data {0b0000'0000};
        unsigned int amountOfOnes = decData%10;
        unsigned int amountOftens = (decData-(decData%10));
        if (amountOftens != 0) {
            amountOftens /= 10;
            data = amountOftens << 4;
        }
        data += amountOfOnes;
        return data;
    }

    unsigned int binDecToDecUni(unsigned int binData, uint8_t shift) {
        binData = revertBits(binData);
        unsigned int data {0}, pow2[8] {1, 2, 4, 8, 16, 32, 64, 128};
        for (int i = 0; i < 8; i++) {
            unsigned int bit = (binData >> i) & 1U;
            if (bit) {
                if (i < shift) {
                    data += pow2[i];
                } else {
                    data += pow2[i - shift] * 10;
                }
            }
        }
        return data;
    }

    unsigned int binYearToDec(unsigned int binData) {
        unsigned int data, shift = 4;
        data = binDecToDecUni(binData, shift);
        return data;
    }

    uint8_t binMonthToDec(uint8_t binData) {
        uint8_t data, shift = 4;
        data = binDecToDecUni(binData, shift);
        return data;
    }


    uint8_t binDayToDec(uint8_t binData) {
        uint8_t data, shift = 4;
        data = binDecToDecUni(binData, shift);
        return data;
    }

    uint8_t binHourToDec(uint8_t binData) {
        uint8_t data, shift = 4;
        data = binDecToDecUni(binData, shift);
        return data;
    }

    uint8_t binSecMinToDec(uint8_t binData) {
        uint8_t data, shift = 4;
        data = binDecToDecUni(binData, shift);
        return data;
    }
}

#endif