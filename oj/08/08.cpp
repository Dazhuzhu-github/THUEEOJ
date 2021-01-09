#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define _Debug
// define global parameters #TODO
//double training[6000][785]; //[0]第一个装正确答案
//double input[500][784]; //测试
double pixel[6000][784];			// 784 = 28 * 28, ??? for length of data 测试样例
int pixel_label[6000]; //各个pixel的label
int sam_label [6]; //有哪些label
float learningRate;//0.1
int M, N=40, L, maxTrainTimes=100;

int num_hidden_layer = 2;		// decide how many hidden layers there are
int num_of_1st_layer_nodes = 100;
int num_of_2nd_layer_nodes = 100;
int hidden_nodes[2] = { num_of_1st_layer_nodes, num_of_2nd_layer_nodes };	// if num_hidden_layer == 2, hidden_nodes = {num_of_1st_layer_nodes, num_of_2nd_layer_nodes};
// inline int readNum() // 快速读入
// {
//     char ch = getchar();
//     while (ch < '0' || ch > '9') ch = getchar();
//     int v = 0;
//     while (ch >= '0' && ch <= '9') {
//         v = v * 10 + ch - '0';
//         ch = getchar();
//     }
//     return v;
// };
/*tools*/
double xavier_uniform(int a, int b){      // xavier_uniform(in_channel, out_channel)权重矩阵初始化
    double gain = 15;					  // choose a number you like, #TODO
    double x = gain * sqrt(6.0 / (a + b));
	return rand() / (RAND_MAX + 1.0) * 2 * x - x;
}
int getMaxIndex(double* arr) {//返回最大
	double maxVal = 0.0;
	int maxIdx = 0;
	for(int i = 0; i < L; ++i)
		if (arr[i] > maxVal) {
			maxVal = arr[i];
			maxIdx = i;
		}
	return maxIdx;
}
void makeOneHot(int label, int* arr) {			//onehot编码,wwx版本
    /* one-hot is an encoding method for classification problem, if labels were "0", "1", "2", 
    their one-hot codes are "001", "010", "100" respectively.*/
	int* output = new int[L];
	for (int i = 0; i < L; ++i)
		output[i] = (i == label) ? 1 : 0;
	arr = output;
	delete[] output;
	//return output;
}
int findIndex(int label, int* label_tag) {
	for (int i = 0; i < L; ++i)
		if (label == label_tag[i])
			return i;
	return 0;
	//记得要delete
}

/*define hidden layers*/
class HiddenLayer{
public:
	HiddenLayer(int in_channel, int out_channel);
	~HiddenLayer();

	void forward(double* input_data);//上层输入，输出，此层节点数
	void backward(double* input_data, double* next_layer_delta, double** next_layer_weight, int next_layer_output);
	void activate_func(double* x);//激活函数 relu max(0,x)
	void activate_func_bp();

	double* output_data;					// the result passed to the next layer
	double* delta;							// needed for back propagation 暂存梯度值
	int in_channel;							// input channel 行 = 784
	int out_channel;							// output channel 列 = 节点数
	double** weight;							// weights of layer 权重
	double* bias;								// bias of layer 偏置
};

HiddenLayer::HiddenLayer(int in, int out){				// initialize network parameters
	in_channel = in;
	out_channel = out;
	weight = new double* [out_channel];
	for(int i = 0; i < out_channel; ++i)
		weight[i] = new double [in_channel];
	bias = new double [out_channel];
	delta = new double[out_channel];
	output_data = new double[out_channel];
	
	for(int i = 0; i < out_channel; ++i){					// weights can not be 0, or would not be trained.
		for(int j = 0; j < in_channel; ++j)
			weight[i][j] = xavier_uniform(in_channel, out_channel);
		bias[i] = xavier_uniform(in_channel, out_channel);
	}
}

HiddenLayer::~HiddenLayer(){
	for(int i = 0; i < out_channel; ++i)
		delete []weight[i];
	delete[] weight;
	delete[] bias;
	delete[] output_data;
	delete[] delta;
}

void HiddenLayer::activate_func(double* x) {
	// #
	for(int i=0;i<out_channel;i++)
	{
		if(x[i]<=0)
		{
			x[i]=0;
		}
		else
		{
			continue;
		}
	}
}

void HiddenLayer::activate_func_bp() {
	// calculate delta #TODO
	double num = 0.0;
	for(int i=0;i<out_channel;i++)
	{
		for(int j=0;j<in_channel;j++)
		{
			num += delta[i]*weight[i][j];
		}
		if(output_data[i]<0)
		{
			delta[i]=0;
		}
		else
		{
			delta[i]=num;
		}
		num = 0.0;
	}
}

void HiddenLayer::forward(double* input_data){
	/*forward data*/
	// calculate between input_data, weight, bias, and get output_data.
	// #
	double num=0;
	for(int i=0;i<out_channel;i++)
	{
		for(int j=0;j<in_channel;j++)
		{
			num += weight[i][j]*input_data[i];
		}
		output_data[i] = num + bias[i];	
		num=0;
	}

	/*activate function*/
	activate_func(output_data);
}
void HiddenLayer::backward(double* input_data, double* next_layer_delta, 
							double** next_layer_weight, int next_layer_outchannel){
/*
	input_data						the input data of i-th layer
	next_layer_delta				the delta of (i+1)th layer
	next_layer_weight			    the weights propagating from i-th layer to (i+1)th layer
	next_layer_outchannel		    the number of outchannel of (i+1)th layer
	*/
	
	/*backpropagate of activate function*/
	// delta = next_layer_delta;
	// weight=next_layer_weight;
	// in_channel = next_layer_outchannel;
	//activate_func_bp();?????
	double num = 0.0;
	for(int i=0;i<out_channel;i++)
	{
		for(int j=0;j<next_layer_outchannel;j++)
		{
			num += next_layer_delta[i]*next_layer_weight[i][j];
		}
		if(output_data[i]<0)
		{
			delta[i]=0;
		}
		else
		{
			delta[i]=num;
		}
		num = 0.0;
	}

	/*backpropagation*/
	// calculate new weights and bias #TODO
	for(int i=0;i<out_channel;i++)
	{
		bias[i] -= learningRate*delta[i];
	}	
	for(int i=0;i<out_channel;i++)
	{
		for(int j=0;j<in_channel;j++)
		{
			weight[i][j] -= learningRate*delta[i]*input_data[j]; 
		}
	}
}

class OutputLayer {								// almost the same with Hiddenlayer, except using softmax as activate function
public:
	OutputLayer(int in_channel, int out_channel);
	~OutputLayer();

	void forward(double* input_data);
	double backward(double* input_data, int* label);
	void softmax(double* x);
	void softmax_bp();
	int eval(double* x);
	
	int in_channel;
	int out_channel;
	double** weight;
	double* bias;
	double* output_data;//最后的输出，记下来
	double* delta; //delta
};

OutputLayer::OutputLayer(int in, int out) {		// initialize network parameters
	in_channel = in;
	out_channel = out;
	weight = new double* [out_channel];
	for (int i = 0; i < out_channel; ++i)
		weight[i] = new double[in_channel];
	bias = new double[out_channel];
	delta = new double[out_channel];
	output_data = new double[out_channel];

	for (int i = 0; i < out_channel; ++i) {
		for (int j = 0; j < in_channel; ++j)
			weight[i][j] = xavier_uniform(in_channel, out_channel);
		bias[i] = xavier_uniform(in_channel, out_channel);
	}	
}

OutputLayer::~OutputLayer(){
	for(int i = 0; i < out_channel; ++i)
		delete []weight[i];
	delete[] weight;
	delete[] bias;
	delete[] output_data;
	delete[] delta;
}

void OutputLayer::softmax(double* x){
	double max = 0.0, sum = 0.0;
	for(int i = 0; i < out_channel; ++i)
		if(max < x[i])
			max = x[i];
	for(int i = 0; i < out_channel; ++i){
		x[i] = exp(x[i] - max);
		sum += x[i];
	}
	for(int i = 0; i < out_channel; ++i)
		x[i] /= sum;
}

void OutputLayer::softmax_bp() {
	// calculate delta #TODO
	for(int i=0;i<out_channel;i++)
	{
		delta[i] = output_data[i]-1;
	}
}

void OutputLayer::forward(double *input_data){
	/*forward data*/
	// calculate between input_data, weight, bias, and get output_data.
	// #TODO
	double num=0;
	for(int i=0;i<out_channel;i++)
	{
		for(int j=0;j<in_channel;j++)
		{
			num += weight[i][j]*input_data[i];
		}
		output_data[i] = num + bias[i];
		num=0;
	}
	/*activate function*/
	softmax(output_data);
}

double OutputLayer::backward(double* input_data, int* label){//交叉信息熵 loss=-ylnp 0.0001
	/*cross entropy loss*/
	double loss = 0.0;
	for (int i = 0; i < L; ++i)
		loss -= label[i] * log(output_data[i]);

	/*backpropagate activate function*/
	softmax_bp();

	/*backpropagation*/
	// calculate new weights and bias #TODO
	for(int i=0;i<out_channel;i++)
	{
		bias[i] -= learningRate*delta[i];
	}	
	for(int i=0;i<out_channel;i++)
	{
		for(int j=0;j<in_channel;j++)
		{
			weight[i][j] -= learningRate*delta[i]*input_data[j]; 
		}
	}
	return loss;
}

int OutputLayer::eval(double* x) {
	forward(x);
	return getMaxIndex(output_data);		// find the max probability which is the most likely prediction
}

class NeuralNetwork {
public:
	NeuralNetwork(int in, int out, int n_hidden_layer, int* hidden_node);
	~NeuralNetwork();

	double train(double* data, int label);
	int* eval();

private:
	int in_channel;
	int out_channel;
	int num_hidden_layer;
	int* hidden_nodes;

	HiddenLayer** layers;
	OutputLayer* last_layer;
};

NeuralNetwork::NeuralNetwork(int in, int out, int n_hidden_layer, int* hidden_node) {
	in_channel = in;
	out_channel = out;
	num_hidden_layer = n_hidden_layer;//有几层
	hidden_nodes = hidden_node;

	layers = new HiddenLayer * [num_hidden_layer];
	for (int i = 0; i < num_hidden_layer; ++i) {
		if (i == 0)
			layers[i] = new HiddenLayer(in_channel, hidden_nodes[i]);				// first hiddenlayer
		else
			layers[i] = new HiddenLayer(hidden_nodes[i - 1], hidden_nodes[i]);		// other hiddenlayers
	}
	last_layer = new OutputLayer(hidden_nodes[num_hidden_layer - 1], out_channel); 	// last layer
}

NeuralNetwork::~NeuralNetwork() {
	for (int i = 0; i < num_hidden_layer; ++i)
		delete layers[i];
	delete[] layers;
	delete last_layer;
}

double NeuralNetwork::train(double* train_data, int label) {
	/*forward*/
	for (int i = 0; i < num_hidden_layer; ++i) {
		if (i == 0)
			layers[i]->forward(train_data);
		else
			layers[i]->forward(layers[i - 1]->output_data);
	}
	last_layer->forward(layers[num_hidden_layer - 1]->output_data);

	/*backward*/
	// to calculate loss, the label need to be preprocessed as one-hot format #
	int* onehot_label;
	makeOneHot(label,onehot_label);//先用int* 试试，原本是double
	double loss = last_layer->backward(layers[num_hidden_layer - 1]->output_data, onehot_label);		

	for (int i = num_hidden_layer - 1; i >= 1; --i) {
		if (i == num_hidden_layer - 1)
			layers[i]->backward(layers[i - 1]->output_data, last_layer->delta, last_layer->weight, last_layer->out_channel);
		else 
			layers[i]->backward(layers[i - 1]->output_data, layers[i + 1]->delta, layers[i + 1]->weight, layers[i + 1]->out_channel);
	}

	if (num_hidden_layer > 1)
		layers[0]->backward(train_data, layers[1]->delta, layers[1]->weight, layers[1]->out_channel);
	else
		layers[0]->backward(train_data, last_layer->delta, last_layer->weight, last_layer->out_channel);

	return loss;
}

int* NeuralNetwork::eval() {			// run forward propagation and get the result
    int* result = new int [M];
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < num_hidden_layer; ++j) {
			if (j == 0)
				layers[j]->forward(pixel[i]);
			else
				layers[j]->forward(layers[j - 1]->output_data);
		}
		result[i] = last_layer->eval(layers[num_hidden_layer - 1]->output_data);
	}
	return result;
}

int main() {
	#ifdef _Debug
    // freopen("7点100组.txt", "r", stdin);
    // freopen("out7.txt", "w", stdout);
    freopen("test.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    // freopen("test2.txt", "r", stdin);
    // freopen("out2.txt", "w", stdout);
    #endif 
	srand(3);				// fixed random seed. change it may be useful, or useless sometimes.
	
	cin>>N>>M>>L;
	/*input training data*/
	// #TODO
	for(int i=0;i<L;i++)
	{
		cin>>sam_label[i];
	}
	for(int i=0;i<N;i++)
	{
		cin>>pixel_label[i];
		for(int j=0;j<=784;j++)
		{
			cin>>pixel[i][j];
		}
	}
	/*define network and train*/
	NeuralNetwork myNet(28 * 28, L, num_hidden_layer, hidden_nodes);
	cout<<"test";
	double accum_loss = 0.0;
	for (int i = 0; i < maxTrainTimes; ++i) {
		int iter = i % N;
		double loss = myNet.train(*(pixel + iter), pixel_label[iter]);
		cout<<loss;
		// accum_loss = (i == 0) ? loss : (accum_loss * 9 + loss) / 10;
		// if (accum_loss < 0.005) {
		// 	std::cout << "stop training at " << i << std::endl;
		// 	break;
		// }
	}
	
	/*input test data*/
	// #TODO
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<=784;j++)
		{
			cin>>pixel[i][j];
		}
	}
	/*evaluation*/
	int* result = new int [M];
	result = myNet.eval();
	/*output results*/
	for(int i=0;i<M;i++)
	{
		cout<<result[i];
		cout<<sam_label[result[i]]<<endl;
	}
	// #TODO
	return 0;
}
