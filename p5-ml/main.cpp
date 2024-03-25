//Project UID db1f506d06d84ab787baf250c265e24e
#include <map>
#include <utility>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "csvstream.h"

using namespace std;

class classifier {
public:
    // Effect: load label, posts, unique_labels, words
    void load_data(csvstream& data) {
        posts_num = 0;
        map<string, string> temp;
        for(int i = 0; data>>temp; i++) {
            labels.push_back(temp["tag"]);
            posts.push_back(temp["content"]);
            unique_labels.insert(temp["tag"]);
            set<string> splitted_words = split_words(temp["content"]);
            words_post.push_back(splitted_words);
            unique_words.insert(splitted_words.begin(), splitted_words.end());
            posts_num++;
        }
        unique_words_num = unique_words.size();
        for(auto &word : unique_words){
            int count = 0;
            for(auto & post: posts){
                if(post.find(word)!=-1) count++;
            }
            posts_num_word[word] = count;
        }
        for (auto &unique_word : unique_words) {
            for (auto &unique_label : unique_labels) {
                int count = 0;
                for (int i = 0; i < posts_num; i++) {
                    if (unique_label == labels[i] &&
                        words_post[i].find(unique_word)!=words_post[i].end())
                        count++;
                }
                pair<string, string> label_word;
                label_word.first = unique_label;
                label_word.second = unique_word;
                posts_num_word_label[label_word] = count;
            }
        }
    };
    
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

    
    // Effect: Debug mode output (training data info, numb of training posts,
    //          vocab size, classes in training data and classifier parameters)
    void debug() {
        cout << "training data:" << endl;
        for (int i = 0; i < posts_num; i++) {
            cout << "  label = " << labels[i] << ", content = " << posts[i] << endl;
        }
        cout << "trained on " << posts_num << " examples" << endl;
        cout << "vocabulary size = " << unique_words_num << endl << endl;
        cout << "classes:" << endl;
        for (auto label : unique_labels) {
            cout<<"  "<<label<<", "<<posts_num_label[label]<<" examples, log-prior = "
            <<log(posts_num_label[label]/posts_num)<<endl;
        }
        cout << "classifier parameters:" << endl;
        for (auto it : posts_num_word_label) {
            if (it.second != 0) {
                cout<<"  "<<it.first.first<<":"<< it.first.second<<", count = "
                << posts_num_word_label[{it.first.first, it.first.second}]
                <<", log-likelihood = "
                <<log(it.second/(double)(posts_num_label[it.first.first]))
                <<endl;
            }
        }
        cout << endl;
    };
    
    double posts_num; // Num of posts
    vector<set<string>> words_post;
    int unique_words_num; // Num of unique words
    set<string> unique_words; // Unique words without repeat found
    set<string> unique_labels; // Unique labels without repeat found
    vector<string> posts; // All posts found
    vector<string> labels; // All labels foun
    
private:
    map<string, int> posts_num_word; //Num of posts contain that word
    map<string, int> posts_num_label; //Num of posts with that label
    map<pair<string,string>, int> posts_num_word_label;
    //Number of posts with that label contain that word
    
    // EFFECTS: Return a set of unique whitespace delimited words.x
    set<string> split_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) words.insert(word);
        return words;
    }
};

int main(int argc, char* argv[]) {
    cout.precision(3);
    //open files and error handling
    ifstream train, test;
    bool debug = false;
    if (argv[3]) debug = !strcmp(argv[3], "--debug");
    if ((argc != 3 && argc != 4) || (argc == 4 && !debug)) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return -1;
    }
    train.open(argv[1]);
    if (!train.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
        return -1;
    }
    test.open(argv[2]);
    if (!test.is_open()) {
        cout << "Error opening file: " << argv[2] << endl;
        return -1;
    }
    classifier train_classifier;
    csvstream train_data(argv[1]);
    train_classifier.load_data(train_data);
    classifier test_classifier;
    csvstream test_data(argv[2]);
    if (debug) train_classifier.debug();
    else cout << "trained on " << train_classifier.posts_num << " examples" << endl;
    train_classifier.print_prediction(test_data);
}


