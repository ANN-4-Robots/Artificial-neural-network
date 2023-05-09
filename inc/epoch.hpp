#ifndef EPOCH_HPP_
#define EPOCH_HPP_

// #include  "matrix.hpp"

class Epoch {

    int trainBatchSize;
    int checkBatchSize;
    int iterationSize;
    std::vector <float> error;
    int totalCount{};
    int goodCount{};

    // Variables containing digit and its corresponding image 
    Idx idx;
    int digit;
    Matrix <float> img;
    Matrix <float> lbl;
    Matrix <float> exp_output;

    public:

    Epoch(int itSize = 10, int trBaSize = 1000, int chBaSize = 100) {
        trainBatchSize = trBaSize;
        checkBatchSize = chBaSize;
        iterationSize = itSize;
        exp_output.reshape(1, 10);
    }

    int train(NeuralNet& nn, sf::RenderWindow &win) {

        long it = iterationSize;
        while (--it) {
            int ba = trainBatchSize;
            while (ba--) {
                // Choose random image from 0-60000
                int n = rand() % 60000;
                getData(n);

                // Learn the neural network 
                nn.backpropagate(reshapeMatrix(img).T(), exp_output.T());
            }

            // After training NN 'trainBatchSize' times it's time
            // To check the progress
            float rightGuessCount{};
            int ch = checkBatchSize;
            Matrix <float> res;
            while (--ch) {
                // Choose random image from 0-60000
                int n = rand() % 60000;
                getData(n);

                // Get guessed result
                res = nn.feedforward(reshapeMatrix(img).T());
                // cout << digit << "\n";
                // cout << res << "\n\n";
                // Find the biggest value
                int mostProb;
                float biggestValue{};
                for(int i = 0; i < res.getSize().first; ++i) {
                    if (biggestValue < res[i][0]) {
                        biggestValue = res[i][0];
                        mostProb = i;
                    }
                }
                ++totalCount;
                if(mostProb == digit) {
                    ++rightGuessCount;
                    ++goodCount;
                }
            }
            error.push_back(rightGuessCount / checkBatchSize);
            cout << rightGuessCount / checkBatchSize << endl;

            updateWindow(win, res, img, totalCount, goodCount, error.back(), digit);
            drawText(win, 10, 600, "Press ENTER to stop learning");

            // Rerender window
            auto retEve = handleEvents(win);
            if(retEve == 1) break;
            else if(retEve == 3) return 1;
            win.display();
        }
        return 0;
    }

    void getData (int n) {

        // Save it to matrix 
        img = idx.getImage(n);
        lbl = idx.getLabel(n);
        digit = int(lbl[0][0]);
        exp_output.fill(0);
        exp_output[0][digit] = 1;
    }
    

    /*
    Epoch() {
        std::thread t1(log({16, 16, 16}, 0.02));
        std::thread t2(log({16, 16, 16}, 0.01));
        std::thread t3(log({16, 16, 16}, 0.03));
        std::thread t4(log({16, 16, 16}, 0.04));
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
    

    int getResult(Matrix<float> results) {
        float highest{};
        int index;
        for (int i = 0; i < results.getSize().first ; ++i) {
            if (results[i][0] > highest) {
                highest = results[i][0];
                index = i;
            }
        }
        return index;
    }



    std::pair<double, double> test(NeuralNet& nn, int amount) {
        double error{};
        int i{};
        while (i < amount) {
            Matrix<float> img = idx.getImage(i);
            Matrix<float> lbl = idx.getLabel(i);
            int digit = int(lbl[0][0]);
            results = nn.feedforward(reshapeMatrix(img).T());
            total ++;
            if (digit == getResult(results))
                good ++;
            error += nn.getError();
        }
        return std::pair(error/amount, double(good)/total*100);
    }
    */
};

#endif