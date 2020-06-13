#include "Network.cpp"

int main()
{
    //////////////////////////LOAD TRAINING DATA///////////////////////////////////
    char file[] = R"(A:\PLAYGROUND\neural_networks\normal_mnist_train.csv)";
    std::vector<int> hidden_layers ={100};
    Network N(784,hidden_layers,10,.85);
    N.load_Data(file, 10000);
    N.init();
    //TODO: OPTIMIZE for LEARNING-RATE
    N.train(R"(A:\PLAYGROUND\neural_networks\model_2)",1,90);
    N.load_model(R"(A:\PLAYGROUND\neural_networks\model_2)");
    N.test(0.1);
    return 0;
}

