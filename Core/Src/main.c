/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fonts.h"
#include "ssd1306.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void adxl_write(uint8_t reg, uint8_t val) {
    uint8_t data[2] = {reg, val};
    HAL_I2C_Master_Transmit(&hi2c1, 0x53 << 1, data, 2, HAL_MAX_DELAY);
}

int16_t adxl_read_axis(uint8_t reg_l) {
    uint8_t data[2];
    HAL_I2C_Master_Transmit(&hi2c1, 0x53 << 1, &reg_l, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, 0x53 << 1, data, 2, HAL_MAX_DELAY);
    return (int16_t)((data[1] << 8) | data[0]);
}

void adxl_init() {
    adxl_write(0x2D, 0x08); // Measurement mode
    adxl_write(0x31, 0x01); // +/-4g
}


//ACS712
float read_current(uint16_t adc_val) {
    float voltage = (adc_val / 4095.0f) * 5.0f;  // Assuming 5V Vref
    float offset = 2.5f;                         // Midpoint voltage
    float sensitivity = 0.066f;                  // 66 mV/A for ACS712-30A
    return (voltage - offset) / sensitivity;     // In Amperes
}

//sound sensor -analog
float read_sound_db(uint16_t adc_val) {
    float voltage = (adc_val / 4095.0f) * 5.0f; // 5V ADC reference
    if (voltage < 0.01f) voltage = 0.01f;       // Prevent log(0)
    return 20.0f * log10f(voltage);             // dB value
}

float read_internal_temp(uint16_t adc_val) {
    float Vsense = (adc_val / 4095.0f) * 3.3f; // Vref = 3.0V
    float temp = ((Vsense - 0.76f) / 0.0025f) + 25.0f; // STM32F4 formula
    return temp;
}



void add_vectors(double *v1, double *v2, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] + v2[i];
}
void mul_vector_number(double *v1, double num, int size, double *result) {
    for(int i = 0; i < size; ++i)
        result[i] = v1[i] * num;
}


void scor(double * input, double * output) {
    double var0[2];
    double var1[2];
    double var2[2];
    double var3[2];
    double var4[2];
    double var5[2];
    double var6[2];
    double var7[2];
    double var8[2];
    double var9[2];
    double var10[2];
    double var11[2];
    double var12[2];
    double var13[2];
    double var14[2];
    double var15[2];
    double var16[2];
    double var17[2];
    double var18[2];
    double var19[2];
    double var20[2];
    double var21[2];
    double var22[2];
    double var23[2];
    double var24[2];
    double var25[2];
    double var26[2];
    double var27[2];
    double var28[2];
    double var29[2];
    double var30[2];
    double var31[2];
    double var32[2];
    double var33[2];
    double var34[2];
    double var35[2];
    double var36[2];
    double var37[2];
    double var38[2];
    double var39[2];
    double var40[2];
    double var41[2];
    double var42[2];
    double var43[2];
    double var44[2];
    double var45[2];
    double var46[2];
    double var47[2];
    double var48[2];
    double var49[2];
    double var50[2];
    double var51[2];
    double var52[2];
    double var53[2];
    double var54[2];
    double var55[2];
    double var56[2];
    double var57[2];
    double var58[2];
    double var59[2];
    double var60[2];
    double var61[2];
    double var62[2];
    double var63[2];
    double var64[2];
    double var65[2];
    double var66[2];
    double var67[2];
    double var68[2];
    double var69[2];
    double var70[2];
    double var71[2];
    double var72[2];
    double var73[2];
    double var74[2];
    double var75[2];
    double var76[2];
    double var77[2];
    double var78[2];
    double var79[2];
    double var80[2];
    double var81[2];
    double var82[2];
    double var83[2];
    double var84[2];
    double var85[2];
    double var86[2];
    double var87[2];
    double var88[2];
    double var89[2];
    double var90[2];
    double var91[2];
    double var92[2];
    double var93[2];
    double var94[2];
    double var95[2];
    double var96[2];
    double var97[2];
    double var98[2];
    double var99[2];
    double var100[2];
    if (input[1] <= 0.24614454805850983) {
        if (input[0] <= 0.4892509523779154) {
            memcpy(var100, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var100, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var100, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    double var101[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[4] <= 0.959867537021637) {
            memcpy(var101, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var101, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[0] <= -0.7760685980319977) {
            memcpy(var101, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var101, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var100, var101, 2, var99);
    double var102[2];
    if (input[4] <= 0.5956993997097015) {
        if (input[5] <= 0.6735003590583801) {
            if (input[3] <= 1.3414318561553955) {
                if (input[2] <= 0.8800712591037154) {
                    memcpy(var102, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var102, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            } else {
                memcpy(var102, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            if (input[1] <= -0.32088348269462585) {
                memcpy(var102, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var102, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        if (input[0] <= -0.1427398193627596) {
            if (input[2] <= 0.5375423729419708) {
                memcpy(var102, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var102, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var102, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var99, var102, 2, var98);
    double var103[2];
    if (input[2] <= 0.09586036950349808) {
        if (input[0] <= 0.16634246706962585) {
            memcpy(var103, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var103, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var103, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var98, var103, 2, var97);
    double var104[2];
    if (input[0] <= 0.13423002511262894) {
        if (input[2] <= 0.03435363294556737) {
            memcpy(var104, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[0] <= -0.7716085314750671) {
                memcpy(var104, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var104, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        memcpy(var104, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var97, var104, 2, var96);
    double var105[2];
    if (input[1] <= 0.24614454805850983) {
        if (input[2] <= 0.34825006779283285) {
            memcpy(var105, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var105, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var105, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var96, var105, 2, var95);
    double var106[2];
    if (input[2] <= 0.09586036950349808) {
        if (input[4] <= 0.9996984004974365) {
            memcpy(var106, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var106, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var106, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var95, var106, 2, var94);
    double var107[2];
    if (input[0] <= 0.036554668098688126) {
        if (input[2] <= 0.5836723856627941) {
            memcpy(var107, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var107, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.4648391604423523) {
            memcpy(var107, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var107, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var94, var107, 2, var93);
    double var108[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[0] <= 0.45981453359127045) {
            memcpy(var108, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var108, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var108, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var93, var108, 2, var92);
    double var109[2];
    if (input[4] <= 0.4249955713748932) {
        if (input[3] <= 0.7416343092918396) {
            if (input[1] <= 0.19198760017752647) {
                memcpy(var109, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var109, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            if (input[5] <= 0.22306851670145988) {
                memcpy(var109, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var109, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        if (input[5] <= -0.34887517988681793) {
            if (input[2] <= -0.5170860588550568) {
                memcpy(var109, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var109, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            if (input[3] <= -0.4656505286693573) {
                if (input[5] <= 0.2272585742175579) {
                    memcpy(var109, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var109, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            } else {
                memcpy(var109, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    }
    add_vectors(var92, var109, 2, var91);
    double var110[2];
    if (input[0] <= 0.08115528523921967) {
        if (input[4] <= 1.1305713057518005) {
            memcpy(var110, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var110, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[2] <= -0.6358576714992523) {
            memcpy(var110, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var110, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var91, var110, 2, var90);
    double var111[2];
    if (input[1] <= 0.23642407357692719) {
        if (input[0] <= 0.5004011057317257) {
            memcpy(var111, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var111, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var111, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var90, var111, 2, var89);
    double var112[2];
    if (input[2] <= 0.10275336261838675) {
        if (input[0] <= 0.16634246706962585) {
            memcpy(var112, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var112, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var112, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var89, var112, 2, var88);
    double var113[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[4] <= 0.959867537021637) {
            memcpy(var113, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var113, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var113, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var88, var113, 2, var87);
    double var114[2];
    if (input[2] <= 0.015795566141605377) {
        memcpy(var114, (double[]){0.0, 1.0}, 2 * sizeof(double));
    } else {
        memcpy(var114, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var87, var114, 2, var86);
    double var115[2];
    if (input[0] <= 0.16634246706962585) {
        if (input[1] <= 0.39889495074748993) {
            memcpy(var115, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var115, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var115, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var86, var115, 2, var85);
    double var116[2];
    if (input[5] <= 0.679785430431366) {
        if (input[4] <= 0.6753611862659454) {
            if (input[4] <= 0.5160376131534576) {
                if (input[1] <= 1.2459654286503792) {
                    memcpy(var116, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var116, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            } else {
                if (input[3] <= 0.7877725586295128) {
                    memcpy(var116, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var116, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            }
        } else {
            memcpy(var116, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[0] <= -0.6846373677253723) {
            memcpy(var116, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var116, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var85, var116, 2, var84);
    double var117[2];
    if (input[0] <= 0.10791565850377083) {
        if (input[4] <= 0.6810513138771057) {
            memcpy(var117, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[3] <= -0.3541496992111206) {
                memcpy(var117, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var117, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        memcpy(var117, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var84, var117, 2, var83);
    double var118[2];
    if (input[4] <= 0.5786290168762207) {
        if (input[2] <= 0.4808076983317733) {
            memcpy(var118, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var118, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.33986155688762665) {
            memcpy(var118, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var118, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var83, var118, 2, var82);
    double var119[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[0] <= 0.14002810046076775) {
            memcpy(var119, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var119, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.33615851402282715) {
            memcpy(var119, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var119, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var82, var119, 2, var81);
    double var120[2];
    if (input[1] <= 0.24614454805850983) {
        if (input[0] <= 0.5677480362355709) {
            memcpy(var120, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var120, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var120, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var81, var120, 2, var80);
    double var121[2];
    if (input[5] <= 0.23982877284288406) {
        if (input[3] <= 1.0376882553100586) {
            if (input[4] <= 0.8915860056877136) {
                memcpy(var121, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var121, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var121, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.2634863555431366) {
            memcpy(var121, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[0] <= -0.1382797658443451) {
                if (input[5] <= 0.4367617666721344) {
                    memcpy(var121, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var121, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            } else {
                memcpy(var121, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    }
    add_vectors(var80, var121, 2, var79);
    double var122[2];
    if (input[0] <= 0.018714420148171484) {
        if (input[5] <= 0.8515780568122864) {
            memcpy(var122, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[3] <= -0.21189004182815552) {
                memcpy(var122, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var122, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        if (input[4] <= -0.9406348764896393) {
            memcpy(var122, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[1] <= -0.48566877841949463) {
                memcpy(var122, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var122, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    }
    add_vectors(var79, var122, 2, var78);
    double var123[2];
    if (input[1] <= 0.2058739960193634) {
        if (input[5] <= 1.0485110580921173) {
            memcpy(var123, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var123, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var123, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var78, var123, 2, var77);
    double var124[2];
    if (input[1] <= 0.17069511115550995) {
        if (input[0] <= 0.4892509523779154) {
            memcpy(var124, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var124, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var124, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var77, var124, 2, var76);
    double var125[2];
    if (input[0] <= 0.04101472906768322) {
        if (input[1] <= 0.6164485663175583) {
            memcpy(var125, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var125, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[4] <= -0.9406348764896393) {
            memcpy(var125, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var125, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var76, var125, 2, var75);
    double var126[2];
    if (input[2] <= 0.1356276534497738) {
        if (input[1] <= 0.6659767180681229) {
            memcpy(var126, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var126, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var126, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var75, var126, 2, var74);
    double var127[2];
    if (input[4] <= 0.6810513138771057) {
        if (input[5] <= 0.6860705316066742) {
            if (input[2] <= 0.8652248051948845) {
                memcpy(var127, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var127, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            if (input[5] <= 1.0966967940330505) {
                if (input[1] <= 0.16606630384922028) {
                    memcpy(var127, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var127, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            } else {
                memcpy(var127, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        memcpy(var127, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var74, var127, 2, var73);
    double var128[2];
    if (input[0] <= 0.10791565850377083) {
        if (input[1] <= 0.6150599271059036) {
            memcpy(var128, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var128, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var128, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var73, var128, 2, var72);
    double var129[2];
    if (input[4] <= 0.3453338146209717) {
        if (input[0] <= 0.31307849660515785) {
            memcpy(var129, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var129, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.3306039571762085) {
            memcpy(var129, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[2] <= -0.583364874124527) {
                memcpy(var129, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var129, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    }
    add_vectors(var72, var129, 2, var71);
    double var130[2];
    if (input[2] <= 0.1356276534497738) {
        if (input[3] <= 1.2145516276359558) {
            if (input[4] <= 1.1362614035606384) {
                memcpy(var130, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var130, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var130, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var130, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var71, var130, 2, var70);
    double var131[2];
    if (input[5] <= 0.47028227150440216) {
        if (input[1] <= 0.24614454805850983) {
            memcpy(var131, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var131, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[0] <= -0.06424273364245892) {
            if (input[2] <= 1.181242123246193) {
                memcpy(var131, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var131, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var131, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var70, var131, 2, var69);
    double var132[2];
    if (input[1] <= 0.23642407357692719) {
        if (input[2] <= 0.34825006779283285) {
            memcpy(var132, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var132, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var132, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var69, var132, 2, var68);
    double var133[2];
    if (input[0] <= 0.15786835178732872) {
        if (input[3] <= 1.0492228269577026) {
            if (input[1] <= 1.2408737391233444) {
                memcpy(var133, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var133, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var133, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var133, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var68, var133, 2, var67);
    double var134[2];
    if (input[2] <= 0.09586036950349808) {
        if (input[1] <= 0.5164665058255196) {
            memcpy(var134, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var134, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var134, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var67, var134, 2, var66);
    double var135[2];
    if (input[1] <= 0.23642407357692719) {
        if (input[5] <= 0.9165240526199341) {
            memcpy(var135, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[3] <= 0.014956489205360413) {
                memcpy(var135, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var135, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        memcpy(var135, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var66, var135, 2, var65);
    double var136[2];
    if (input[1] <= 0.04849478509277105) {
        if (input[5] <= 1.452852189540863) {
            memcpy(var136, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var136, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[2] <= -0.08494821935892105) {
            memcpy(var136, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var136, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var65, var136, 2, var64);
    double var137[2];
    if (input[1] <= 0.250310480594635) {
        if (input[2] <= 0.3811243586242199) {
            memcpy(var137, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var137, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var137, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var64, var137, 2, var63);
    double var138[2];
    if (input[4] <= 0.4249955713748932) {
        if (input[0] <= 0.19800890982151031) {
            if (input[5] <= 2.30972021818161) {
                memcpy(var138, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var138, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var138, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[4] <= 0.6753611862659454) {
            if (input[0] <= 0.058408960700035095) {
                memcpy(var138, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var138, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var138, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var63, var138, 2, var62);
    double var139[2];
    if (input[4] <= 0.5956993997097015) {
        if (input[0] <= 0.23190538212656975) {
            if (input[1] <= 0.6164485663175583) {
                memcpy(var139, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var139, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var139, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.3338441103696823) {
            memcpy(var139, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var139, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var62, var139, 2, var61);
    double var140[2];
    if (input[4] <= 0.6753611862659454) {
        if (input[1] <= 0.20818839222192764) {
            if (input[5] <= 1.6916858553886414) {
                memcpy(var140, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var140, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            if (input[0] <= -0.2694055736064911) {
                memcpy(var140, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var140, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        if (input[2] <= -0.5011791437864304) {
            memcpy(var140, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var140, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var61, var140, 2, var60);
    double var141[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[0] <= 0.16634246706962585) {
            memcpy(var141, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var141, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var141, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var60, var141, 2, var59);
    double var142[2];
    if (input[0] <= 0.036554668098688126) {
        if (input[4] <= 1.4662887752056122) {
            if (input[2] <= 0.5836723856627941) {
                memcpy(var142, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var142, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var142, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[5] <= -0.4515317231416702) {
            if (input[1] <= 0.033219754695892334) {
                memcpy(var142, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var142, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var142, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var59, var142, 2, var58);
    double var143[2];
    if (input[2] <= 0.09586036950349808) {
        if (input[4] <= 1.0964305400848389) {
            memcpy(var143, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var143, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var143, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var58, var143, 2, var57);
    double var144[2];
    if (input[2] <= 0.1356276534497738) {
        if (input[4] <= 0.959867537021637) {
            memcpy(var144, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var144, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var144, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var57, var144, 2, var56);
    double var145[2];
    if (input[1] <= 0.23642407357692719) {
        if (input[5] <= 0.9626147449016571) {
            memcpy(var145, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[2] <= -0.016018271446228027) {
                memcpy(var145, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var145, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        memcpy(var145, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var56, var145, 2, var55);
    double var146[2];
    if (input[1] <= 0.2058739960193634) {
        if (input[2] <= 0.5412539653480053) {
            memcpy(var146, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var146, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[2] <= -0.4115701988339424) {
            memcpy(var146, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var146, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var55, var146, 2, var54);
    double var147[2];
    if (input[1] <= 0.04849478509277105) {
        if (input[0] <= 0.5267154723405838) {
            memcpy(var147, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var147, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[2] <= -0.30075203627347946) {
            if (input[2] <= -0.4470956474542618) {
                memcpy(var147, (double[]){1.0, 0.0}, 2 * sizeof(double));
            } else {
                memcpy(var147, (double[]){0.0, 1.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var147, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var54, var147, 2, var53);
    double var148[2];
    if (input[4] <= 0.6696710586547852) {
        if (input[5] <= 0.6735003590583801) {
            if (input[0] <= 0.7274182587862015) {
                memcpy(var148, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var148, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            if (input[3] <= 0.7762380242347717) {
                if (input[1] <= -0.16952170431613922) {
                    memcpy(var148, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var148, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            } else {
                memcpy(var148, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        if (input[4] <= 0.7550229132175446) {
            if (input[1] <= -0.26209772378206253) {
                memcpy(var148, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var148, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var148, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var53, var148, 2, var52);
    double var149[2];
    if (input[0] <= 0.14002810046076775) {
        if (input[3] <= 0.9223425388336182) {
            if (input[2] <= 0.6101839356124401) {
                memcpy(var149, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var149, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            if (input[4] <= 0.6184598803520203) {
                memcpy(var149, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var149, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        memcpy(var149, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var52, var149, 2, var51);
    double var150[2];
    if (input[0] <= 0.13423002511262894) {
        if (input[3] <= 1.0492228269577026) {
            if (input[5] <= 2.160973012447357) {
                if (input[1] <= 1.0228572338819504) {
                    memcpy(var150, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var150, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            } else {
                memcpy(var150, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var150, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var150, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var51, var150, 2, var50);
    double var151[2];
    if (input[4] <= 0.5956993997097015) {
        if (input[1] <= 0.23642407357692719) {
            memcpy(var151, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var151, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[0] <= -0.1587960422039032) {
            if (input[5] <= 0.04708583652973175) {
                memcpy(var151, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var151, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var151, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var50, var151, 2, var49);
    double var152[2];
    if (input[0] <= 0.15786835178732872) {
        if (input[5] <= 1.1385974287986755) {
            if (input[3] <= 1.6528652906417847) {
                if (input[5] <= 0.9416644275188446) {
                    if (input[2] <= 0.8068994646891952) {
                        memcpy(var152, (double[]){0.0, 1.0}, 2 * sizeof(double));
                    } else {
                        memcpy(var152, (double[]){1.0, 0.0}, 2 * sizeof(double));
                    }
                } else {
                    if (input[5] <= 1.017085611820221) {
                        memcpy(var152, (double[]){1.0, 0.0}, 2 * sizeof(double));
                    } else {
                        memcpy(var152, (double[]){0.0, 1.0}, 2 * sizeof(double));
                    }
                }
            } else {
                memcpy(var152, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var152, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var152, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var49, var152, 2, var48);
    double var153[2];
    if (input[2] <= 0.09586036950349808) {
        if (input[3] <= 1.2145516276359558) {
            if (input[4] <= 1.2557541131973267) {
                memcpy(var153, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var153, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var153, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var153, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var48, var153, 2, var47);
    double var154[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[0] <= 0.45981453359127045) {
            memcpy(var154, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var154, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var154, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var47, var154, 2, var46);
    double var155[2];
    if (input[1] <= 0.04849478509277105) {
        if (input[5] <= 1.452852189540863) {
            memcpy(var155, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var155, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[2] <= -0.30075203627347946) {
            if (input[3] <= 0.7300997376441956) {
                memcpy(var155, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var155, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var155, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var46, var155, 2, var45);
    double var156[2];
    if (input[0] <= 0.08115528523921967) {
        if (input[5] <= 0.8515780568122864) {
            if (input[2] <= 0.8397737555205822) {
                memcpy(var156, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var156, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            if (input[1] <= 0.30169014632701874) {
                memcpy(var156, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var156, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        memcpy(var156, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var45, var156, 2, var44);
    double var157[2];
    if (input[0] <= 0.04101472906768322) {
        if (input[1] <= 0.6164485663175583) {
            memcpy(var157, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var157, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var157, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var44, var157, 2, var43);
    double var158[2];
    if (input[4] <= 0.6753611862659454) {
        if (input[0] <= 0.2800740450620651) {
            if (input[0] <= -0.0629047118127346) {
                memcpy(var158, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                if (input[5] <= 1.9137591868638992) {
                    memcpy(var158, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var158, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            }
        } else {
            memcpy(var158, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[2] <= -0.5595044791698456) {
            memcpy(var158, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var158, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var43, var158, 2, var42);
    double var159[2];
    if (input[1] <= 0.23503543436527252) {
        if (input[0] <= 0.8005632907152176) {
            memcpy(var159, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var159, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var159, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var42, var159, 2, var41);
    double var160[2];
    if (input[4] <= 0.37947455048561096) {
        if (input[2] <= 0.5386028056964278) {
            memcpy(var160, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var160, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.26904091238975525) {
            memcpy(var160, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var160, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var41, var160, 2, var40);
    double var161[2];
    if (input[5] <= 0.5394183099269867) {
        if (input[1] <= 0.24614454805850983) {
            memcpy(var161, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var161, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.330141082406044) {
            memcpy(var161, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var161, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var40, var161, 2, var39);
    double var162[2];
    if (input[2] <= 0.09586036950349808) {
        if (input[1] <= 0.5734007209539413) {
            memcpy(var162, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var162, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var162, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var39, var162, 2, var38);
    double var163[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[0] <= 0.45981453359127045) {
            memcpy(var163, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var163, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var163, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var38, var163, 2, var37);
    double var164[2];
    if (input[1] <= 0.17069511115550995) {
        if (input[0] <= 0.5079832039773464) {
            memcpy(var164, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var164, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[0] <= -0.694895476102829) {
            memcpy(var164, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var164, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var37, var164, 2, var36);
    double var165[2];
    if (input[0] <= 0.13423002511262894) {
        if (input[1] <= 0.6164485663175583) {
            memcpy(var165, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var165, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var165, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var36, var165, 2, var35);
    double var166[2];
    if (input[0] <= -0.047740502282977104) {
        memcpy(var166, (double[]){0.0, 1.0}, 2 * sizeof(double));
    } else {
        if (input[0] <= 0.10791565850377083) {
            if (input[3] <= 0.17644044756889343) {
                memcpy(var166, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var166, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var166, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var35, var166, 2, var34);
    double var167[2];
    if (input[5] <= 0.5394183099269867) {
        if (input[1] <= 0.24614454805850983) {
            memcpy(var167, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var167, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[2] <= -0.5361743569374084) {
            memcpy(var167, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[1] <= -0.6310130655765533) {
                memcpy(var167, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var167, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    }
    add_vectors(var34, var167, 2, var33);
    double var168[2];
    if (input[1] <= 0.23642407357692719) {
        if (input[2] <= 0.3811243586242199) {
            memcpy(var168, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var168, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var168, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var33, var168, 2, var32);
    double var169[2];
    if (input[1] <= 0.041088704485446215) {
        if (input[2] <= 0.7894018557853997) {
            memcpy(var169, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var169, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= 0.24892184138298035) {
            if (input[4] <= 0.396544948220253) {
                memcpy(var169, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var169, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var169, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var32, var169, 2, var31);
    double var170[2];
    if (input[1] <= 0.05636374466121197) {
        if (input[2] <= 0.7894018557853997) {
            memcpy(var170, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var170, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= 0.17069511115550995) {
            if (input[3] <= 0.20335444435477257) {
                memcpy(var170, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var170, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var170, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var31, var170, 2, var30);
    double var171[2];
    if (input[0] <= 0.16634246706962585) {
        if (input[4] <= 1.511809766292572) {
            if (input[2] <= 0.8397737555205822) {
                memcpy(var171, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var171, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var171, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var171, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var30, var171, 2, var29);
    double var172[2];
    if (input[1] <= 0.23642407357692719) {
        if (input[0] <= 0.5267154723405838) {
            memcpy(var172, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var172, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var172, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var29, var172, 2, var28);
    double var173[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[4] <= 0.9996984004974365) {
            memcpy(var173, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var173, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var173, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var28, var173, 2, var27);
    double var174[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[1] <= 0.4812876209616661) {
            memcpy(var174, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var174, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var174, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var27, var174, 2, var26);
    double var175[2];
    if (input[2] <= 0.04920008685439825) {
        if (input[4] <= 0.9996984004974365) {
            memcpy(var175, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var175, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var175, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var26, var175, 2, var25);
    double var176[2];
    if (input[1] <= 0.05636374466121197) {
        if (input[5] <= 1.1239322423934937) {
            memcpy(var176, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var176, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[0] <= -0.694895476102829) {
            memcpy(var176, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[2] <= -0.30075203627347946) {
                if (input[4] <= 1.04521943628788) {
                    memcpy(var176, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var176, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            } else {
                memcpy(var176, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    }
    add_vectors(var25, var176, 2, var24);
    double var177[2];
    if (input[2] <= 0.09586036950349808) {
        if (input[4] <= 0.9996984004974365) {
            memcpy(var177, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var177, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var177, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var24, var177, 2, var23);
    double var178[2];
    if (input[2] <= 0.015795566141605377) {
        if (input[0] <= 0.16634246706962585) {
            memcpy(var178, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var178, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var178, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var23, var178, 2, var22);
    double var179[2];
    if (input[4] <= 0.5900092720985413) {
        if (input[0] <= 0.19800890982151031) {
            memcpy(var179, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var179, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[3] <= -0.7693941593170166) {
            if (input[4] <= 0.8176143169403076) {
                memcpy(var179, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var179, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var179, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var22, var179, 2, var21);
    double var180[2];
    if (input[4] <= 0.6753611862659454) {
        if (input[0] <= 0.19800890982151031) {
            if (input[1] <= 0.6164485663175583) {
                memcpy(var180, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var180, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var180, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.5027953386306763) {
            memcpy(var180, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var180, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var21, var180, 2, var20);
    double var181[2];
    if (input[4] <= 0.6753611862659454) {
        if (input[0] <= 0.19800890982151031) {
            if (input[1] <= 0.6164485663175583) {
                memcpy(var181, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var181, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var181, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var181, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var20, var181, 2, var19);
    double var182[2];
    if (input[0] <= 0.036554668098688126) {
        if (input[5] <= 0.8955737352371216) {
            memcpy(var182, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var182, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[0] <= 0.13423002511262894) {
            if (input[3] <= 0.7416343241930008) {
                memcpy(var182, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var182, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var182, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var19, var182, 2, var18);
    double var183[2];
    if (input[2] <= -0.105096984654665) {
        if (input[1] <= 0.7895657271146774) {
            memcpy(var183, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var183, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[3] <= -1.0423789322376251) {
            memcpy(var183, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[3] <= -0.6079102158546448) {
                if (input[4] <= -0.34317155182361603) {
                    memcpy(var183, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var183, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            } else {
                memcpy(var183, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    }
    add_vectors(var18, var183, 2, var17);
    double var184[2];
    if (input[2] <= 0.03435363294556737) {
        if (input[1] <= 0.5359074622392654) {
            memcpy(var184, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var184, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var184, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var17, var184, 2, var16);
    double var185[2];
    if (input[5] <= 0.5980792045593262) {
        if (input[0] <= 0.22699931263923645) {
            if (input[3] <= 0.07262933254241943) {
                memcpy(var185, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                if (input[2] <= 0.7342578917741776) {
                    memcpy(var185, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var185, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            }
        } else {
            memcpy(var185, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.330141082406044) {
            memcpy(var185, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var185, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var16, var185, 2, var15);
    double var186[2];
    if (input[0] <= 0.08115528523921967) {
        if (input[4] <= 0.6810513138771057) {
            if (input[0] <= -0.07316285744309425) {
                memcpy(var186, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                if (input[2] <= 0.30795253813266754) {
                    memcpy(var186, (double[]){0.0, 1.0}, 2 * sizeof(double));
                } else {
                    memcpy(var186, (double[]){1.0, 0.0}, 2 * sizeof(double));
                }
            }
        } else {
            if (input[1] <= 0.5368331968784332) {
                memcpy(var186, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var186, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        memcpy(var186, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var15, var186, 2, var14);
    double var187[2];
    if (input[0] <= 0.036554668098688126) {
        if (input[1] <= 0.6164485663175583) {
            memcpy(var187, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var187, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.318569079041481) {
            memcpy(var187, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var187, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var14, var187, 2, var13);
    double var188[2];
    if (input[0] <= 0.018714420148171484) {
        if (input[2] <= 0.04920008685439825) {
            memcpy(var188, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var188, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[4] <= 0.026686695870012045) {
            if (input[3] <= 0.5763054937124252) {
                memcpy(var188, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var188, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var188, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var13, var188, 2, var12);
    double var189[2];
    if (input[4] <= 0.6753611862659454) {
        if (input[2] <= 0.31590602919459343) {
            memcpy(var189, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var189, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var189, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var12, var189, 2, var11);
    double var190[2];
    if (input[2] <= 0.14464157447218895) {
        if (input[5] <= 1.4151416420936584) {
            if (input[1] <= 0.5359074622392654) {
                memcpy(var190, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var190, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var190, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var190, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var11, var190, 2, var10);
    double var191[2];
    if (input[1] <= 0.24614454805850983) {
        if (input[2] <= 0.5439051203429699) {
            memcpy(var191, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var191, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var191, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var10, var191, 2, var9);
    double var192[2];
    if (input[1] <= 0.24614454805850983) {
        if (input[0] <= 0.5267154723405838) {
            memcpy(var192, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var192, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var192, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var9, var192, 2, var8);
    double var193[2];
    if (input[4] <= 0.37947455048561096) {
        if (input[2] <= 0.4749751500785351) {
            memcpy(var193, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var193, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[5] <= -0.032525368966162205) {
            if (input[1] <= 0.38732296228408813) {
                memcpy(var193, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var193, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            if (input[2] <= -0.5080721378326416) {
                memcpy(var193, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var193, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    }
    add_vectors(var8, var193, 2, var7);
    double var194[2];
    if (input[4] <= 0.6753611862659454) {
        if (input[1] <= 0.3479781597852707) {
            memcpy(var194, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var194, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var194, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var7, var194, 2, var6);
    double var195[2];
    if (input[0] <= 0.10791565850377083) {
        if (input[2] <= 0.04920008685439825) {
            memcpy(var195, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            if (input[3] <= -0.00042293965816497803) {
                memcpy(var195, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var195, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        }
    } else {
        memcpy(var195, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var6, var195, 2, var5);
    double var196[2];
    if (input[1] <= 0.17069511115550995) {
        if (input[2] <= 1.058758955448866) {
            memcpy(var196, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var196, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= 0.23503543436527252) {
            if (input[1] <= 0.22624070942401886) {
                memcpy(var196, (double[]){1.0, 0.0}, 2 * sizeof(double));
            } else {
                memcpy(var196, (double[]){0.0, 1.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var196, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var5, var196, 2, var4);
    double var197[2];
    if (input[4] <= 0.6810513138771057) {
        if (input[0] <= 0.1716945432126522) {
            if (input[1] <= 0.6164485663175583) {
                memcpy(var197, (double[]){0.0, 1.0}, 2 * sizeof(double));
            } else {
                memcpy(var197, (double[]){1.0, 0.0}, 2 * sizeof(double));
            }
        } else {
            memcpy(var197, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        if (input[1] <= -0.5027953386306763) {
            memcpy(var197, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var197, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    }
    add_vectors(var4, var197, 2, var3);
    double var198[2];
    if (input[2] <= 0.03435363294556737) {
        if (input[0] <= 0.14002810046076775) {
            memcpy(var198, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var198, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var198, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var3, var198, 2, var2);
    double var199[2];
    if (input[0] <= 0.08115528523921967) {
        if (input[1] <= 0.6150599271059036) {
            memcpy(var199, (double[]){0.0, 1.0}, 2 * sizeof(double));
        } else {
            memcpy(var199, (double[]){1.0, 0.0}, 2 * sizeof(double));
        }
    } else {
        memcpy(var199, (double[]){1.0, 0.0}, 2 * sizeof(double));
    }
    add_vectors(var2, var199, 2, var1);
    mul_vector_number(var1, 0.01, 2, var0);
    memcpy(output, var0, 2 * sizeof(double));
}
void score(double *input, double *output) {
    // input[0] = vibration_x
    // input[1] = vibration_y
    // input[2] = vibration_z
    // input[3] = temperature
    // input[4] = noise


    if (input[0] > 9.0 || input[1] > 15.0 || input[2] > 8.0 ||
        input[3] > 100.0 || input[4] > 100.00) {
        output[0] = 1.0;  // Fault
        output[1] = 0.0;
    } else {
        output[0] = 0.0;
        output[1] = 1.0;  // Good
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */







  char msg[128];
  #define N 100
  int16_t x_vals[N], y_vals[N], z_vals[N];
  int32_t x_sum = 0, y_sum = 0, z_sum = 0;
  uint8_t i = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  	adxl_init();


	    int16_t x = adxl_read_axis(0x32);
	    int16_t y = adxl_read_axis(0x34);
	    int16_t z = adxl_read_axis(0x36);

	    x_vals[i] = x;
	    y_vals[i] = y;
	    z_vals[i] = z;
	    x_sum += x;
	    y_sum += y;
	    z_sum += z;
	    i++;

	    if (i == N) {
	      float x_avg = x_sum / N;
	      float y_avg = y_sum / N;
	      float z_avg = z_sum / N;

	      uint32_t x_sq = 0, y_sq = 0, z_sq = 0;
	      for (int j = 0; j < N; j++) {
	        float dx = x_vals[j] - x_avg;
	        float dy = y_vals[j] - y_avg;
	        float dz = z_vals[j] - z_avg;
	        x_sq += dx * dx;
	        y_sq += dy * dy;
	        z_sq += dz * dz;
	      }

	      float x_rms = sqrtf(x_sq / (float)N);
	      float y_rms = sqrtf(y_sq / (float)N);
	      float z_rms = sqrtf(z_sq / (float)N);

	      HAL_ADC_Start(&hadc1);
	      HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	      uint16_t ch0 = HAL_ADC_GetValue(&hadc1); // sound analog

	      HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	      uint16_t ch1 = HAL_ADC_GetValue(&hadc1); // current

	      HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	      uint16_t ch2 = HAL_ADC_GetValue(&hadc1); // temp
	      HAL_ADC_Stop(&hadc1);

	      float sound_analog = read_sound_db(ch0);
	      float temp_c = read_internal_temp(ch2);
	      float current = read_current(ch1);
	      uint8_t sound_digital = (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET);

	      // DISPLAY
	      SSD1306_Init();
	      char buffer[32];
	      SSD1306_Fill(SSD1306_COLOR_BLACK);
	      double input[5] = {x_rms, y_rms, z_rms, temp_c, sound_analog};  // Set appropriate vars
	      double output[2]={0,0};
	      score(input, output);


//	      snprintf(msg, sizeof(msg), "Score inputs: X:%.2f Y:%.2f Z:%.2f T:%.2f dB:%.2f => %.1f/%.1f\r\n",
//	               input[0], input[1], input[2], input[3], input[4], output[0], output[1]);
//	      HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);


	      if (output[0] == 1.0) {
	          SSD1306_Fill(SSD1306_COLOR_BLACK);
	          SSD1306_DrawRectangle(5, 15, 118, 50, SSD1306_COLOR_WHITE);
	          SSD1306_GotoXY(20, 24);
	          SSD1306_Puts("!FAULT!", &Font_11x18, 1);
	          SSD1306_GotoXY(14, 44);
	          SSD1306_Puts("ERROR DETECTED", &Font_7x10, 1);

	      } else {
	          snprintf(buffer, sizeof(buffer), "X:%.4f", x_rms);
	          SSD1306_GotoXY(0, 0);
	          SSD1306_Puts(buffer, &Font_7x10, 1);

	          snprintf(buffer, sizeof(buffer), "Y:%.4f", y_rms);
	          SSD1306_GotoXY(0, 12);
	          SSD1306_Puts(buffer, &Font_7x10, 1);

	          snprintf(buffer, sizeof(buffer), "Z:%.4f", z_rms);
	          SSD1306_GotoXY(0, 24);
	          SSD1306_Puts(buffer, &Font_7x10, 1);

	          snprintf(buffer, sizeof(buffer), "dB:%.2f", sound_analog);
	          SSD1306_GotoXY(0, 36);
	          SSD1306_Puts(buffer, &Font_7x10, 1);


	          snprintf(buffer, sizeof(buffer), "T:%.2fC", temp_c);
	          SSD1306_GotoXY(0, 48);
	          SSD1306_Puts(buffer, &Font_7x10, 1);
	      }

	      SSD1306_UpdateScreen();

	      snprintf(msg, sizeof(msg),
	        "RMS=>X:%.4f Y:%.4f Z:%.4f | Sound:%.2f dB | Temp:%.4f C | Impulse:%u\r\n",
	        x_rms, y_rms, z_rms, sound_analog, temp_c, sound_digital);
	      HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	      HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	      x_sum = y_sum = z_sum = 0;
	      i = 0;
	    }

	    HAL_Delay(10);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 3;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 2;
  sConfig.SamplingTime = ADC_SAMPLETIME_144CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = 3;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PC0 PC1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
