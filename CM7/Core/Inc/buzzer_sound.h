/**
 * @file buzzer_sound.h
 * @brief PWM-based buzzer control
 * @details Provides functionality to play a melody using a PWM-controlled buzzer
 */

#ifndef INC_BUZZER_SOUND_H_
#define INC_BUZZER_SOUND_H_

/* External Variables */

/** @brief Timer handle for PWM generation */

extern TIM_HandleTypeDef htim1;

/** @brief Array of notes in Hz for the melody */

extern int melody_tones[];

/** @brief Array of note durations in milliseconds for the melody */

extern int melody_durations[];

/** @brief Array of pause durations between notes in milliseconds for the melody */

extern int melody_pauses[];

/** @brief Size of the melody array */

extern size_t melody_size;

/* Defines */

/** @brief Timer clock frequency in Hz */

#define TIM_FREQ 240000000

/* Function Prototypes */

/**
 * @brief Stop playing the current tone
 * @return None
 *
 * @note Sets the timer prescaler to 0 to effectively stop PWM output
 */

void stop_playing_tone(void);

/**
 * @brief Calculate timer prescaler value for desired frequency
 * @param frequency Desired frequency in Hz
 * @return Timer prescaler value
 *
 * @note Calculation based on timer clock frequency (TIM_FREQ)
 *       Returns 0 if frequency is 0 to prevent division by zero
 */

int calculate_prescaler_for_frequency(int frequency);

/**
 * @brief Play a sequence of tones with specified durations and pauses
 * @param tones Array of tones in Hz
 * @param durations Array of note durations in milliseconds
 * @param pauses Array of pause durations between notes in milliseconds
 * @param size Number of notes in the sequence
 * @return None
 *
 * @note The function blocks until the entire sequence is played
 */

void play_melody(int *tones, int *durations, int *pauses, size_t size);

#endif /* INC_BUZZER_SOUND_H_ */
