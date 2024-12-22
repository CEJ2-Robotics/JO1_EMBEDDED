/**
 * @file buzzer_sound.c
 * @brief Implementation of buzzer sound functions
 */

#include "main.h"
#include "buzzer_sound.h"

/* Global Variables */

/**
 * @brief Predefined melody sequence tones in Hz
 * @note Values correspond to musical notes (e.g., 131 Hz = C3, 165 Hz = E3, etc.)
 */

int melody_tones[] =
{
	131, 165, 196, 247, 262, 247, 196, 165, 131, 165, 196, 247, 262,
	247, 196, 165, 131, 165, 196, 247, 262, 247, 196, 165, 131, 165,
	196, 247, 262, 247, 196, 165, 131, 165, 196, 247, 262, 247, 196,
	165, 131, 165, 196, 247, 262, 247, 196, 165
};

/**
 * @brief Duration of each note in milliseconds
 * @note 188 ms corresponds to approximately 1/16th note at 80 BPM
 */

int melody_durations[] =
{
	188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188,
	188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188,
	188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188,
	188, 188, 188, 188, 188, 188, 188, 188, 188
};

/**
 * @brief Pause duration between notes in milliseconds
 * @note 50 ms provides a short break between notes for clarity
 */

int melody_pauses[] =
{
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50
};

/** @brief Calculate the size of melody array at compile time */

size_t melody_size = sizeof(melody_durations) / sizeof(melody_durations[0]);

/* Functions */

void stop_playing_tone(void)
{
    __HAL_TIM_SET_PRESCALER(&htim1, 0);
}

int calculate_prescaler_for_frequency(int frequency)
{
	if (frequency == 0) return 0;
    return ((TIM_FREQ / (1000 * frequency)) - 1);
}

void play_melody(int *tones, int *durations, int *pauses, size_t size)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);  // Start PWM for the buzzer

    for (int i = 0; i < size; i++)
    {
        int prescaler = calculate_prescaler_for_frequency(tones[i]);
        int duration = durations[i];
        int pause = pauses ? pauses[i] : 0;

        // Set the prescaler to adjust the frequency

        __HAL_TIM_SET_PRESCALER(&htim1, prescaler);

        // Play the tone for the specified duration

        HAL_Delay(duration);

        // Stop the tone

        stop_playing_tone();

        // Delay between tones

        HAL_Delay(pause);
    }
}
