#include "main.h"
#include "kalman_pos.h"

void kalman_init(kalman_filter_t *kf, float x, float y, float angle) {

	kf->state.x = x;
	kf->state.y = y;
	kf->state.angle = angle;

	// Initialize covariance matrix P

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			kf->P[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}

	// Initialize process noise covariance Q

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			kf->Q[i][j] = (i == j) ? 0.01 : 0.0;
		}
	}

	// Initialize measurement noise covariance R

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			kf->R[i][j] = (i == j) ? 1.0 : 0.0;
		}
	}
}

void kalman_predict(kalman_filter_t *kf, float encoder_distance, float imu_angle) {

	float angle_rad = imu_angle * M_PI / 180.0;

    // Predict new state

    kf->state.x += encoder_distance * cos(angle_rad);
    kf->state.y += encoder_distance * sin(angle_rad);
    kf->state.angle = imu_angle;

    // Update covariance matrix P

    float F[3][3] = {
        {1.0, 0.0, -encoder_distance * sin(angle_rad)},
        {0.0, 1.0, encoder_distance * cos(angle_rad)},
        {0.0, 0.0, 1.0}
    };

    float P_new[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            P_new[i][j] = 0.0;
            for (int k = 0; k < 3; k++) {
                P_new[i][j] += F[i][k] * kf->P[k][j];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            kf->P[i][j] = P_new[i][j] + kf->Q[i][j];
        }
    }
}

void kalman_update(kalman_filter_t *kf, vehicle_coordinates_t camera_coords) {

    // Innovation (measurement residual)

    float y[3] = {
        camera_coords.x - kf->state.x,
        camera_coords.y - kf->state.y,
        camera_coords.angle - kf->state.angle
    };

    // Innovation covariance S

    float S[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            S[i][j] = kf->P[i][j] + kf->R[i][j];
        }
    }

    // Calculate Kalman gain K

    float K[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            K[i][j] = 0.0;
            for (int k = 0; k < 3; k++) {
                K[i][j] += kf->P[i][k] * (1.0 / S[k][j]);
            }
        }
    }

    // Update state estimate

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            kf->state.x += K[i][j] * y[j];
            kf->state.y += K[i][j] * y[j];
            kf->state.angle += K[i][j] * y[j];
        }
    }

    // Update covariance matrix P

    float I[3][3] = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };

    float P_new[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            P_new[i][j] = I[i][j];
            for (int k = 0; k < 3; k++) {
                P_new[i][j] -= K[i][k] * kf->P[k][j];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            kf->P[i][j] = P_new[i][j];
        }
    }
}
