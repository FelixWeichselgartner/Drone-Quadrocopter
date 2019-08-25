#include "Arduino.h"
#include "MPUHandler.hpp"
#include "math.h"

<<<<<<< HEAD
/**
 * @brief  calculation of a rotation matrix.
 * @note   
 * @param  R[3][3]: 
 * @param  angleDegree: 
 * @retval None
 */
void getZRotationMatrix(float R[3][3], int angleDegree) {
=======
void getZRotationMatrix(float R[3][3], int angleDegree)
{
>>>>>>> 4fe791ce3cadd5dbe25d6db1ab755fc9229e7da6
    float angle = angleDegree / 180 * M_PI;
    float Rs[3][3] = {
        cos(angle), -sin(angle), 0,
        sin(angle), cos(angle), 0,
        0, 0, 1};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            R[i][j] = Rs[i][j];
        }
    }
}

<<<<<<< HEAD
/**
 * @brief  constructor.
 * @note   calculates a rotation matrix and reset.
 * @retval 
 */
MPUHandler::MPUHandler() {
=======
MPUHandler::MPUHandler()
{
>>>>>>> 4fe791ce3cadd5dbe25d6db1ab755fc9229e7da6
    getZRotationMatrix(this->R, 45);
    reset();
}

<<<<<<< HEAD
/**
 * @brief  checks if communication to mpu module is possible.
 * @note   if not starts endless loop.
 * @retval None
 */
void MPUHandler::reset() {
    int status = mpu.begin();
    if (status < 0) {
        while(1) {}
=======
void MPUHandler::reset()
{
    int status = mpu.begin();
    if (status < 0)
    {
        /*
        Serial.println("IMU initialization unsuccessful");
        Serial.println("Check IMU wiring or try cycling power");
        Serial.print("Status: ");
        Serial.println(status);
        */
        while (1)
        {
        }
>>>>>>> 4fe791ce3cadd5dbe25d6db1ab755fc9229e7da6
    }
}

// matrix shapes.
// M x P * P x N = M x N
#define m 1
#define p 3
#define n 3
/**
 * @brief  matrix multiplication.
 * @note   
 * @param  mat1[1][3]: vector
 * @param  mat2[3][3]: matrix
 * @param  res[1][3]: vector
 * @retval None
 */
void matmul(float mat1[1][3],
            float mat2[3][3],
            float res[1][3])
{

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

<<<<<<< HEAD
/**
 * @brief  converts angles from the gravitation acceleration vector.
 * @note   
 * @param  v[m][n]: vector
 * @param  ax: angle in x
 * @param  ay: angle in y
 * @retval None
 */
void vektorToAngle(float v[m][n], float& ax, float& ay) {
    ax = atan(v[0][0]/(sqrt(v[0][1]*v[0][1] + v[0][2]*v[0][2])));
    ay = atan(v[0][1]/(sqrt(v[0][0]*v[0][0] + v[0][2]*v[0][2])));
}

/**
 * @brief  calculates x and y angle
 * @note   used in regulator.
 * @param  &ax: 
 * @param  &ay: 
 * @retval None
 */
void MPUHandler::calculateAngles(float &ax, float &ay) {
=======
void vektorToAngle(float v[m][n], float &ax, float &ay)
{
    ax = atan(v[0][0] / (sqrt(v[0][1] * v[0][1] + v[0][2] * v[0][2])));
    ay = atan(v[0][1] / (sqrt(v[0][0] * v[0][0] + v[0][2] * v[0][2])));
}

void MPUHandler::calculateAngles(float &ax, float &ay)
{
>>>>>>> 4fe791ce3cadd5dbe25d6db1ab755fc9229e7da6
    float acc[1][3];
    float acc_R[1][3];

    mpu.readSensor();
    acc[0][0] = mpu.getAccelX_mss();
    acc[0][1] = mpu.getAccelY_mss();
    acc[0][2] = mpu.getAccelZ_mss();

    matmul(acc, this->R, acc_R);
    vektorToAngle(acc_R, ax, ay);
}