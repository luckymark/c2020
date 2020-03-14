//
// Created by asus on 2020/3/14.
//

#include "Neural_Networks_Functions.h"
#include <math.h>
#include <stdlib.h>

void init_simple(sample *pSample, int num_x)
{
    pSample->y_fact = 0.0;
    pSample->x = (double*)malloc(sizeof(double) * num_x);
    for(int i = 0; i < num_x; ++i) {
        pSample->x[i] = 0.0;
    }
}
void init_node(node *pNode, int num_sample, int num_x, sample *samples1)
{
    pNode->samples = samples1;
    pNode->y_predict = (double*)malloc(sizeof(double) * num_sample);
    //pNode->cost_value = 0.0;
    for(int i = 0; i < num_x; ++i) {
        pNode->dw[i] = 0.0;
        pNode->w[i] = 0.0;
    }
    pNode->db = 0.0;
    pNode->b = 0.0;
}

double sigmoid(double z)
{
    return 1.0 / (1.0 + exp(-z));
}

double y_predict_simple(const double *w, const double *x, double b, int num_x)
{
    double y = b;
    for(int i = 0; i < num_x; ++i) {
        y += w[i] * x[i];
    }
    return sigmoid(y);
}

//double lost(double y_predict, double y_fact)
//{
//    return -(y_fact * log(y_predict) + (1.0 - y_fact) * log(1.0-y_predict));
//}

//double cost(node* train1)
//{
//    double sum_lost = 0;
//    for(int i = 0; i < SIMPLE_SIZE ; ++i) {
//        sum_lost += lost(train1->samples[i].y_predict,train1->samples[i].y_fact);
//    }
//    return sum_lost / SIMPLE_SIZE;
//}

void db_SimpleContribution(node *pNode, int sample_value)
{
    pNode->db += pNode->y_predict[sample_value] - pNode->samples[sample_value].y_fact;
}

void dw_SimpleContribution(node *pNode, int samp_val, int num_x)
{
    for(int i = 0; i < num_x; ++i) {
        pNode->dw[i] += pNode->samples[samp_val].x[i] * (pNode->y_predict[samp_val] - pNode->samples[samp_val].y_fact);
    }
}

void dw_db_average(node *pNode, int num_x)
{
    for(int i = 0; i < num_x; ++i) {
        pNode->dw[i] /= SIMPLE_SIZE;
    }
    pNode->db /= SIMPLE_SIZE;
}

void update_w_b(node *pNode, int num_x)
{
    for(int i = 0; i < num_x; ++i) {
        pNode->w[i] -= LEARN_RATE * pNode->dw[i];
    }
    pNode->b -= LEARN_RATE * pNode->db;
}

void train_node(node *pNode, int num_x)
{
    // loop for every sample
    for(int i = 0; i < SIMPLE_SIZE; ++i) {
        pNode->y_predict[i] = y_predict_simple(pNode->w, pNode->samples[i].x, pNode->b, num_x);
        dw_SimpleContribution(pNode, i, num_x);
        db_SimpleContribution(pNode, i);
    }
    //pNode->cost_value = cost(pNode);
    dw_db_average(pNode, num_x);
    update_w_b(pNode, num_x);
}
