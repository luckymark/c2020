//
// Created by asus on 2020/3/14.
//

#ifndef NEURAL_NETWORKS_NEURAL_NETWORKS_FUNCTIONS_H
#define NEURAL_NETWORKS_NEURAL_NETWORKS_FUNCTIONS_H

#define LINE 8
#define ROW 8
#define SIMPLE_SIZE 15 // 样本数
#define NUM_INPUT_NODE (LINE * ROW)
#define NUM_OUTPUT_NODE 10 // 0 1 2 3 4 5 6 7 8 9
#define LEARN_RATE 1


typedef struct __SIMPLE__ {
    double y_fact;
    double* x;
} sample;

typedef struct __NODE__ {
    sample* samples;
    double* y_predict;
    double b;
    double w[LINE * ROW];
    double dw[LINE * ROW];
    double db;
    //double cost_value;
} node;


void init_simple(sample *pSample, int num_x);
void init_node(node *pNode, int num_sample, int num_x, sample *samples1);
double sigmoid(double z);
double y_predict_simple(const double *w, const double *x, double b, int num_x);
void dw_SimpleContribution(node *pNode, int samp_val, int num_x);
void db_SimpleContribution(node *pNode, int sample_value);
void dw_db_average(node *pNode, int num_x);
void update_w_b(node *pNode, int num_x);

void train_node(node *pNode, int num_x);

//double lost(double y_predict, double y_fact);
//double cost(node* train1);

#endif //NEURAL_NETWORKS_NEURAL_NETWORKS_FUNCTIONS_H
