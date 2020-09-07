#include <iostream>
#include <vector>

class User
{
public:
    friend class SocialNetwork;
    using ID = size_t;

    ID id() const {
        return UserId;
    }

    size_t degree() const
    {
        return UserFriends.size();
    }

void addFriend(const User& friendUser)
{
   UserFriends.push_back(friendUser);
   // for (int i = 0; i<UserFriends.size();i++)
   // {
   //     std::cout<<UserFriends[i].name;
   // }
}

void friendList()
{  
   std::cout<<"Friends of "<<name<<"\n";
   for (int i = 0; i<UserFriends.size(); i++)
   {
       std::cout<<UserFriends[i].name<<"\n";
   }
}

private:
    ID UserId;
    std::string name;
std::vector<User> UserFriends;
};

class SocialNetwork
{
public:
    size_t totalUsers = 0;
    std::vector<User> UserVector;
    User::ID addUser(std::string name)
    {
        class User* newUser = new User;
        newUser->name = name;
        newUser->UserId = totalUsers;
        UserVector.push_back(*newUser);
        totalUsers++;
        return newUser->UserId;
    }
   
    SocialNetwork& addFriendship(User::ID originalUser, User::ID friendUser)
    {
        UserVector[originalUser].addFriend(UserVector[friendUser]);
        UserVector[friendUser].addFriend(UserVector[originalUser]);
    }
   
User& getUser(User::ID findUser)
{
//    std::cout<<UserVector[findUser].name;
   return UserVector[findUser];
}

struct Iterator
{
User& operator*();
Iterator operator ++ (int);

bool operator == (const Iterator&) const;
bool operator != (const Iterator&) const;
};

    void outputVector()
    {
        for (int i = 0; i < UserVector.size(); i++)
        {
            std::cout << UserVector[i].name << "\n"<<UserVector[i].UserId <<"\n";
            std::cout << UserVector[i].degree();
        }
    }
   
    void outputFriends(User::ID userID)
    {
        UserVector[userID].friendList();
    }

private:

};

int main()
{
    SocialNetwork Facebook;
    Facebook.addUser("Tousif Habib");
    Facebook.addUser("Mo Adem");
    Facebook.addUser("Aymen Abu");
    Facebook.addUser("Jonathan Anderson");
    Facebook.addFriendship(0,2);
    Facebook.addFriendship(0,1);
    Facebook.addFriendship(0,3);
    Facebook.addFriendship(3,2);
    Facebook.outputFriends(0);
    Facebook.outputFriends(3);
//    Facebook.outputVector();
//    Facebook.getUser(0);
}
