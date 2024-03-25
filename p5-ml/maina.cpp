//Project UID db1f506d06d84ab787baf250c265e24e

#include "csvstream.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include<math.h>
using namespace std;

class Classifier {
private:
    int num_posts;
    bool debug;
    

    map<pair<string,string>, int> posts_num_word_label;
    //Number of posts with that label contain that word
    map<string, int> posts_num_word; //Num of posts contain that word
    map<string, int> posts_num_label; //Num of posts with that label
    
    
    set<string> unique_words(const string &str) {
      istringstream source(str);
      set<string> words;
      string word;
      while (source >> word) {
        words.insert(word);
      }
      return words;
    }
    
public:
    
    Classifier(bool debug_mode): num_posts(0), debug(debug_mode){
        
    }
    
   
    void train(csvstream &csvin) {
        map<string, string> row;
        if(debug){
            cout << "training data:" << endl;
        }
        while (csvin >> row) {
            if(debug) {
                cout << "  label = " << row["tag"] <<
                ", content = " << row["content"] << endl;
            }
            
            lables_posts[row["tag"]]++;
            
            set<string> content = unique_words(row["content"]);
            for(auto word:content) {
                word_posts[word]++;
                data[row["tag"]][word]++;
               
            }
            
            num_posts++;
            
           
        }
        cout<< "trained on " << num_posts << " examples"<<endl;
        if(debug){
            cout << "vocabulary size = "<< word_posts.size() << endl;
            cout<< "classes:"<<endl;
            for (auto k: data) {
                double log_prob = log(lables_posts[k.first]/(double)num_posts);
                cout<< "  " << k.first << ", " << lables_posts[k.first]
                <<" examples, log-prior = " << log_prob <<endl;
            }
            cout<< "classifier parameters:" <<endl;
            for (auto k: data) {
                for (auto word:k.second) {
                    double log_like = log(word.second/(double)lables_posts[k.first]);
                    cout<< "  "<<k.first<< ":" << word.first<<", count = "
                    << word.second<<", log-likelihood = "<<log_like<<endl;
                }
                
            }
        }
        cout << endl;
        
    }
    
    
    // conditional prob part (on training dataset)
    double calculate_probability(string & post, string & label) {
        set<string> words = split_words(post);
        double prob = log(posts_num_label[label]/(double)posts_num); //lnP(C)
        for(auto & word: words) {
            //lnP(w|C), when w appears in C during training
            if(posts_num_word_label[{label, word}] != 0) {
                prob += log(posts_num_word_label[{label, word}]
                            /(double)posts_num_label[label]);
            }
            //lnP(w|C), when w not appears in C but in overall data during training
            else if(//posts_num_word_label[{label, word}] == 0 &&
                    posts_num_word[word] != 0) {
                prob += log(posts_num_word[word]/(double)posts_num);
            }
            //lnP(w|C), when w not appears in overall data during training
            else
                prob += log(1/(double)posts_num);
        }
        return prob;
    }
    
    // Effect: Output the label with highest probability score
    pair<string, double> predict(string &post, vector<string> labels){
        pair<string, double> result;
        double prob = calculate_probability(post, labels[0]);
        string correct_label = labels[0];
        for(auto & label: labels){
            double current = calculate_probability(post,label);
            if(current > prob) {
                prob = current;
                correct_label = label;
            }
            else if(current == prob){
                if(correct_label.compare(label) > 0)
                    correct_label = label;
            }
        }
        result.first = correct_label;
        result.second = prob;
        return result;
    }
    
    void print_prediction(csvstream &csv){
        cout<< "test data:" << endl;
        int total_posts = 0;
        int correct_posts = 0;
        map<string,string> a_post;
        while(csv>>a_post){
            ++total_posts;
            string correct_tag = a_post["tag"];
            string contents = a_post["content"];
            pair<string, double> stuff = predict(contents, labels);
            if(stuff.first == correct_tag)
                ++correct_posts;
            
            cout << "  correct = " << correct_tag << ", predicted = "
            << stuff.first << ", log-probability score = " << stuff.second <<endl;
            cout<< "  content = " << contents <<endl;
            cout<<endl;
        }
        cout<< "performance: "<< correct_posts<< " / "
        <<total_posts<< " posts predicted correctly"<<endl;
    }
   
};

int main(int argc, char*argv[]) {
    //error checking
    bool debug = false;
    cout.precision(3);
    if ((argc != 3 && argc != 4)) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }
    
//
    if (argc == 4) {
        string debug_string = "--debug";
        string debug_string2(argv[3]);
        if (debug_string!=debug_string2) {
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return -1;
        }
        else {
            debug = true;
        }
    }
    
    
    string filename1 = argv[1];
    string filename2 = argv[2];

    csvstream train(filename1);
    if (!train) {
        cout << "Error opening file: " << filename1 << endl;
    }
    csvstream predict(filename2);
    if(!predict) {
        cout << "Error opening file: " << filename2 << endl;
    }
  
    Classifier helper(debug);
    helper.train(train);
    helper.print_predict_outcome(predict);
    return 0;
}
