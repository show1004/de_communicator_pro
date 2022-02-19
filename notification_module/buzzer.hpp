
#ifndef HAL_BUZZER_MODULE_H
#define HAL_BUZZER_MODULE_H


/**
 * @file buzzer.hpp
 * @author Mohammad Hefny
 * @brief 
 * @version 0.1
 * @date 2022-02-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
  


#include "notification.hpp"

namespace notification
{

class CBuzzer: public CNotification
{
    public:
        //https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
        static CBuzzer& getInstance()
        {
            static CBuzzer instance;

            return instance;
        }

        CBuzzer(CBuzzer const&)                  = delete;
        void operator=(CBuzzer const&)           = delete;

    private:

        CBuzzer()
        {
            
        }

    public:
        
        ~CBuzzer (){};

    public:
        // Patterns - how many beeps will be played; read from
        // left-to-right, each bit represents 100ms
        static const uint32_t    SINGLE_BUZZ = 0b10000000000000000000000000000000UL;
        static const uint32_t    DOUBLE_BUZZ = 0b10100000000000000000000000000000UL;
        static const uint32_t    ARMING_BUZZ = 0b11111111111111111111111111111100UL; // 3s
        static const uint32_t      BARO_BUZZ = 0b10101010100000000000000000000000UL;
        static const uint32_t        EKF_BAD = 0b11101101010000000000000000000000UL;

    public:

        bool init (const std::vector<PORT_STATUS>& buzzer_pins);
        void update() override;
        void uninit() override;  

        void switchBuzzer(const uint8_t buzzer_index, const bool onOff, const uint32_t tone);
        
        /// on - turns the buzzer on or off
        void on(const uint8_t buzzer_index, const bool turn_on);

        
    private:

        
        
        /// play_pattern - plays the defined buzzer pattern
        void play_pattern(const uint32_t pattern);

        /// buzzer_flag_type - bitmask of current state and ap_notify states we track
        uint32_t _pattern;           // current pattern
        uint8_t _pin;
        uint32_t _pattern_start_time;

        // enforce minumum 100ms interval between patterns:
        const uint64_t _pattern_start_interval_time_us = (32*100 + 100) * 1000; 

        void update_playing_pattern();
        void update_pattern_to_play();


    private:
    bool m_turn_on= false;
    struct buzzer_flag_type {
        bool m_fcb_connected = false;
        bool m_is_online = false;
    }   m_flags;
};

};
#endif

