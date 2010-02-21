
#ifndef PETREL_H
#define PETREL_H

#include <QObject>
#include <QtNetwork>
#include "../petrel_types.h"

enum ATTR_TYPE {
    ATTR_ROLE
};

//autogenerated enum
enum ROLE_TYPE {
    AVAILABLE_TRENDS,BLOCKING_IDS_BLOCKS,CREATE_BLOCK,CREATE_FAVORITE,CREATE_FRIENDSHIP,CREATE_SAVED_SEARCH,DELETE_LIST_ID,DELETE_LIST_MEMBER,DELETE_LIST_SUBSCRIBER,DESTROY,DESTROY_BLOCK,DESTROY_DIRECT_MESSAGE,DESTROY_FAVORITE,DESTROY_FRIENDSHIP,DESTROY_SAVED_SEARCH,DIRECT_MESSAGES,EXISTS_FRIENDSHIPS,FAVORITES,FOLLOW_NOTIFICATION,FOLLOWERS,FRIENDS,FRIENDS_TIMELINE,GET_LIST_ID,GET_LIST_MEMBERS,GET_LIST_MEMBERS_ID,GET_LIST_MEMBERSHIPS,GET_LIST_STATUSES,GET_LIST_SUBSCRIBERS,GET_LIST_SUBSCRIBERS_ID,GET_LIST_SUBSCRIPTIONS,GET_LISTS,HOME_TIMELINE,IDS_FOLLOWERS,IDS_FRIENDS,LEAVE_NOTIFICATION,LOCATION_TRENDS,MENTIONS,NEW_DIRECT_MESSAGE,POST_LIST,POST_LIST_MEMBER,POST_LIST_SUBSCRIBER,POST_LISTS_ID,PUBLIC_TIMELINE,RATE_LIMIT_STATUS,REPORT_SPAM,RETWEET,RETWEETED_BY_ME,RETWEETED_TO_ME,RETWEETS,RETWEETS_OF_ME,SAVED_SEARCHES,SEARCH_USERS,SENT_DIRECT_MESSAGES,SHOW,SHOW_FRIENDSHIPS,SHOW_SAVED_SEARCH,SHOW_USERS,TEST_HELP,UPDATE,UPDATE_DELIVERY_DEVICE,UPDATE_PROFILE,UPDATE_PROFILE_BACKGROUND_IMAGE,UPDATE_PROFILE_COLOR,UPDATE_PROFILE_IMAGE,USER_TIMELINE,VERIFY_CREDENTIALS
};

class Petrel : public QObject
{
    Q_OBJECT
public:
    Petrel(const QString& userid, const QString& pass);
    virtual ~Petrel();
    //BEGIN auto generated methods
    void availableTrends(const QString& lat, const QString& long_);
    void blocking_IdsBlocks();
    void createBlock(quint64 id, quint64 user_id, const QString& screen_name);
    void createFavorite(quint64 id);
    void createFriendship(quint64 id, quint64 user_id, const QString& screen_name, const QString& follow);
    void createSavedSearch(const QString& query);
    void deleteListId(quint64 id, quint64 list_id);
    void deleteListMember(quint64 list_id, quint64 id);
    void deleteListSubscriber(const QString& user, quint64 list_id, quint64 id);
    void destroy(quint64 id);
    void destroyBlock(quint64 id, quint64 user_id, const QString& screen_name);
    void destroyDirectMessage(quint64 id);
    void destroyFavorite(quint64 id);
    void destroyFriendship(quint64 id, quint64 user_id, const QString& screen_name);
    void destroySavedSearch(quint64 id);
    void directMessages(quint64 since_id, quint64 max_id, int count, int page);
    void existsFriendships(const QString& user_a, const QString& user_b);
    void favorites(quint64 id, int page);
    void followNotification(quint64 id, quint64 user_id, const QString& screen_name);
    void followers(quint64 id, quint64 user_id, const QString& screen_name, qint64 cursor);
    void friends(quint64 id, quint64 user_id, const QString& screen_name, qint64 cursor);
    void friendsTimeline(quint64 since_id, quint64 max_id, int count, int page);
    void getListId(quint64 id, quint64 list_id);
    void getListMembers(quint64 list_id, qint64 cursor, quint64 id);
    void getListMembersId(quint64 list_id, quint64 id);
    void getListMemberships(qint64 cursor, quint64 list_id, quint64 id);
    void getListStatuses(quint64 since_id, quint64 max_id, const QString& per_page, int page, quint64 list_id, quint64 id);
    void getListSubscribers(quint64 list_id, qint64 cursor, quint64 id);
    void getListSubscribersId(const QString& user, quint64 list_id, quint64 id);
    void getListSubscriptions(qint64 cursor, quint64 list_id, quint64 id);
    void getLists(qint64 cursor, quint64 list_id, quint64 id);
    void homeTimeline(quint64 since_id, quint64 max_id, int count, int page);
    void idsFollowers(qint64 cursor);
    void idsFriends(qint64 cursor);
    void leaveNotification(quint64 id, quint64 user_id, const QString& screen_name);
    void locationTrends(const QString& woeid);
    void mentions(quint64 since_id, quint64 max_id, int count, int page);
    void newDirectMessage(const QString& user, const QString& text);
    void postList(const QString& name, const QString& mode, const QString& description, quint64 list_id, quint64 id);
    void postListMember(quint64 list_id, quint64 id);
    void postListSubscriber(quint64 list_id, quint64 id);
    void postListsId(const QString& name, const QString& mode, const QString& description, quint64 list_id, quint64 id);
    void publicTimeline();
    void rateLimitStatus();
    void reportSpam(quint64 id, quint64 user_id, const QString& screen_name);
    void retweet(quint64 id);
    void retweetedByMe(quint64 since_id, quint64 max_id, int count, int page);
    void retweetedToMe(quint64 since_id, quint64 max_id, int count, int page);
    void retweets(quint64 id, int count);
    void retweetsOfMe(quint64 since_id, quint64 max_id, int count, int page);
    void savedSearches();
    void searchUsers(const QString& q, const QString& per_page, int page);
    void sentDirectMessages(quint64 since_id, quint64 max_id, int count, int page);
    void show(quint64 id);
    void showFriendships(quint64 source_id, const QString& source_screen_name, quint64 target_id, const QString& target_screen_name);
    void showSavedSearch(quint64 id);
    void showUsers(quint64 id, quint64 user_id, const QString& screen_name);
    void testHelp();
    void update(const QString& status, quint64 in_reply_to_status_id, const QString& lat, const QString& long_);
    void updateDeliveryDevice(const QString& device);
    void updateProfile(const QString& name, const QString& url, const QString& location, const QString& description);
    void updateProfileBackgroundImage(const QString& image, const QString& tile);
    void updateProfileColor(const QString& profile_background_color, const QString& profile_text_color, const QString& profile_link_color, const QString& profile_sidebar_fill_color, const QString& profile_sidebar_border_color);
    void updateProfileImage(const QString& image);
    void userTimeline(quint64 id, quint64 user_id, const QString& screen_name, quint64 since_id, quint64 max_id, int count, int page);
    void verifyCredentials();
    //END auto generated methods
    void issueGetRequest(QNetworkRequest& req);
    void issuePostRequest(QNetworkRequest& req, QByteArray& data);
    void issuePutRequest(QNetworkRequest& req, QByteArray& data);
    void issueDeleteRequest(QNetworkRequest& req);
signals:
    //BEGIN auto generated signals
    void availableTrendsReceived(locations_t& locations);
    void blocking_IdsBlocksReceived(ids_t& ids);
    void createBlockReceived(user_t& user);
    void createFavoriteReceived(status_t& status);
    void createFriendshipReceived(user_t& user);
    void createSavedSearchReceived(saved_search_t& saved_search);
    void deleteListIdReceived(list_t& list);
    void deleteListMemberReceived(list_t& list);
    void deleteListSubscriberReceived(list_t& list);
    void destroyReceived(status_t& status);
    void destroyBlockReceived(user_t& user);
    void destroyDirectMessageReceived(direct_message_t& direct_message);
    void destroyFavoriteReceived(status_t& status);
    void destroyFriendshipReceived(user_t& user);
    void destroySavedSearchReceived(saved_search_t& saved_search);
    void directMessagesReceived(direct_messages_t& direct_messages);
    void existsFriendshipsReceived(friends_t& friends);
    void favoritesReceived(statuses_t& statuses);
    void followNotificationReceived(user_t& user);
    void followersReceived(users_t& users, quint64 next, quint64 prev);
    void friendsReceived(users_t& users, quint64 next, quint64 prev);
    void friendsTimelineReceived(statuses_t& statuses);
    void getListIdReceived(list_t& list);
    void getListMembersReceived(users_list_t& users_list);
    void getListMembersIdReceived(user_t& user);
    void getListMembershipsReceived(lists_list_t& lists_list);
    void getListStatusesReceived(statuses_t& statuses);
    void getListSubscribersReceived(users_list_t& users_list);
    void getListSubscribersIdReceived(user_t& user);
    void getListSubscriptionsReceived(lists_list_t& lists_list);
    void getListsReceived(lists_list_t& lists_list);
    void homeTimelineReceived(statuses_t& statuses);
    void idsFollowersReceived(id_list_t& id_list);
    void idsFriendsReceived(id_list_t& id_list);
    void leaveNotificationReceived(user_t& user);
    void locationTrendsReceived(matching_trends_t& matching_trends);
    void mentionsReceived(statuses_t& statuses);
    void newDirectMessageReceived(direct_message_t& direct_message);
    void postListReceived(list_t& list);
    void postListMemberReceived(list_t& list);
    void postListSubscriberReceived(list_t& list);
    void postListsIdReceived(list_t& list);
    void publicTimelineReceived(statuses_t& statuses);
    void rateLimitStatusReceived(hash_t& hash);
    void reportSpamReceived(user_t& user);
    void retweetReceived(status_t& status);
    void retweetedByMeReceived(statuses_t& statuses);
    void retweetedToMeReceived(statuses_t& statuses);
    void retweetsReceived(statuses_t& statuses);
    void retweetsOfMeReceived(statuses_t& statuses);
    void savedSearchesReceived(saved_searches_t& saved_searches);
    void searchUsersReceived(users_t& users);
    void sentDirectMessagesReceived(direct_messages_t& direct_messages);
    void showReceived(status_t& status);
    void showFriendshipsReceived(relationship_t& relationship);
    void showSavedSearchReceived(saved_search_t& saved_search);
    void showUsersReceived(user_t& user);
    void testHelpReceived(ok_t& ok);
    void updateReceived(status_t& status);
    void updateDeliveryDeviceReceived(user_t& user);
    void updateProfileReceived(user_t& user);
    void updateProfileBackgroundImageReceived(user_t& user);
    void updateProfileColorReceived(user_t& user);
    void updateProfileImageReceived(user_t& user);
    void userTimelineReceived(statuses_t& statuses);
    void verifyCredentialsReceived(user_t& user);
    //END auto generated signals

public slots:
    void replyFinished( QNetworkReply* );
private:
    QNetworkAccessManager *m_manager;
    QString m_userid;
    QString m_pass;
};

#endif // PETREL_H
