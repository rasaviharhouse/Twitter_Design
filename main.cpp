#include <iostream>
#include <unordered_set>
#include <queue>

using namespace std;

class Tweet {
    public:

    int tweetId;
    int userId;
    int tweet_time;

    Tweet(int tweetId, int userId, int tweet_order) {
        this -> tweetId = tweetId;
        this -> userId = userId;
        this -> tweet_time = tweet_order;
    }
};


class Twitter {
public:

    int tweet_order;
    unordered_map<int, unordered_set<int>> followers;
    unordered_map<int, unordered_set<int>> following;
    unordered_map<int, unordered_set<int>> user_tweets;
    unordered_map<int, Tweet*> tweets_db;
    priority_queue<pair<int, int>>pq;

    Twitter() {
        tweet_order = 1;
    }

    void postTweet(int userId, int tweetId) {
        tweets_db[tweetId] = new Tweet(tweetId, userId, tweet_order);
        tweet_order++;
        user_tweets[userId].insert(tweetId);
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> feed;
        int k = 10;
        reset_feed();
        for(int followee: following[userId]){
            for(int tweet: user_tweets[followee]){
                pq.push({tweets_db[tweet]->tweet_time, tweet});
            }
        }
        for(int tweet: user_tweets[userId]){
            pq.push({tweets_db[tweet]->tweet_time, tweet});
        }

        while(!pq.empty() && k--) {
            feed.push_back(pq.top().second);
            pq.pop();
        }
        return feed;
    }

    void reset_feed() {
        while(!pq.empty()) pq.pop();
    }

    void follow(int followerId, int followeeId) {
        following[followerId].insert(followeeId);
        followers[followeeId].insert(followerId);
    }

    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
        followers[followeeId].erase(followerId);
    }
};


/**
 * The Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */