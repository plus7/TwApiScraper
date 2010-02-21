#include "petrel.h"

Petrel::Petrel(const QString& id, const QString& pass)
        :m_manager(new QNetworkAccessManager( this )),
        m_id(id),m_pass(pass)
{
    connect(m_manager,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(replyFinished(QNetworkReply*)));
}

Petrel::~Petrel()
{
}

//HTTP
void Petrel::issueGetRequest(QNetworkRequest& req){
    QByteArray auth = m_id.toUtf8() + ":" + m_pass.toUtf8();
    req.setRawHeader( "Authorization", auth.toBase64().prepend( "Basic " ) );
    m_manager->get(req);
}

void Petrel::issuePostRequest(QNetworkRequest& req, QByteArray& data, bool multipart){

}

void Petrel::issuePutRequest(QNetworkRequest& req, QByteArray& data){

}

void Petrel::issueDeleteRequest(QNetworkRequest& req){

}

//BEGIN autogenerated methods
void Petrel::availableTrends(const QString& lat, const QString& long){

    QString requestStr("http://api.twitter.com/1/trends/available.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(lat!="") requestUrl.addQueryItem("lat",lat);
    if(long!="") requestUrl.addQueryItem("long",long);
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), AVAILABLE_TRENDS);
    issueGetRequest(req);
    
}
void Petrel::blocking_IdsBlocks(){

    QString requestStr("http://api.twitter.com/1/blocks/blocking/ids.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), BLOCKING_IDS_BLOCKS);
    issueGetRequest(req);
    
}
void Petrel::createBlock(quint64 id, quint64 user_id, const QString& screen_name){

}
void Petrel::createFavorite(quint64 id){

}
void Petrel::createFriendship(quint64 id, quint64 user_id, const QString& screen_name, const QString& follow){

}
void Petrel::createSavedSearch(const QString& query){

}
void Petrel::deleteListId(quint64 id, quint64 list_id){

}
void Petrel::deleteListMember(quint64 list_id, quint64 id){

}
void Petrel::deleteListSubscriber(const QString& user, quint64 list_id, quint64 id){

}
void Petrel::destroy(quint64 id){

}
void Petrel::destroyBlock(quint64 id, quint64 user_id, const QString& screen_name){

}
void Petrel::destroyDirectMessage(quint64 id){

}
void Petrel::destroyFavorite(quint64 id){

}
void Petrel::destroyFriendship(quint64 id, quint64 user_id, const QString& screen_name){

}
void Petrel::destroySavedSearch(quint64 id){

}
void Petrel::directMessages(quint64 since_id, quint64 max_id, int count, int page){

    QString requestStr("http://api.twitter.com/1/direct_messages.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), DIRECT_MESSAGES);
    issueGetRequest(req);
    
}
void Petrel::existsFriendships(const QString& user_a, const QString& user_b){

    QString requestStr("http://api.twitter.com/1/friendships/exists.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(user_a!="") requestUrl.addQueryItem("user_a",user_a);
    if(user_b!="") requestUrl.addQueryItem("user_b",user_b);
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), EXISTS_FRIENDSHIPS);
    issueGetRequest(req);
    
}
void Petrel::favorites(quint64 id, int page){

    QString requestStr("http://api.twitter.com/1/favorites.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), FAVORITES);
    issueGetRequest(req);
    
}
void Petrel::followNotification(quint64 id, quint64 user_id, const QString& screen_name){

}
void Petrel::followers(quint64 id, quint64 user_id, const QString& screen_name, qint64 cursor){

    QString requestStr("http://api.twitter.com/1/statuses/followers.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    if(user_id!=0) requestUrl.addQueryItem("user_id",QString::number(user_id,10));
    if(screen_name!="") requestUrl.addQueryItem("screen_name",screen_name);
    if(cursor!=0) requestUrl.addQueryItem("cursor",QString::number(cursor,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), FOLLOWERS);
    issueGetRequest(req);
    
}
void Petrel::friends(quint64 id, quint64 user_id, const QString& screen_name, qint64 cursor){

    QString requestStr("http://api.twitter.com/1/statuses/friends.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    if(user_id!=0) requestUrl.addQueryItem("user_id",QString::number(user_id,10));
    if(screen_name!="") requestUrl.addQueryItem("screen_name",screen_name);
    if(cursor!=0) requestUrl.addQueryItem("cursor",QString::number(cursor,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), FRIENDS);
    issueGetRequest(req);
    
}
void Petrel::friendsTimeline(quint64 since_id, quint64 max_id, int count, int page){

    QString requestStr("http://api.twitter.com/1/statuses/friends_timeline.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), FRIENDS_TIMELINE);
    issueGetRequest(req);
    
}
void Petrel::getListId(quint64 id, quint64 list_id){

    QString requestStr("http://api.twitter.com/1/"+m_user+"/lists/"+QString::number(id,10)+".xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(list_id!=0) requestUrl.addQueryItem("list_id",QString::number(list_id,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), GET_LIST_ID);
    issueGetRequest(req);
    
}
void Petrel::getListMembers(quint64 list_id, qint64 cursor, quint64 id){

    QString requestStr("http://api.twitter.com/1/"+m_user+"/"+QString::number(list_id,10)+"/members.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(cursor!=0) requestUrl.addQueryItem("cursor",QString::number(cursor,10));
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), GET_LIST_MEMBERS);
    issueGetRequest(req);
    
}
void Petrel::getListMembersId(quint64 list_id, quint64 id){

    QString requestStr("http://api.twitter.com/1/"+m_user+"/"+QString::number(list_id,10)+"/members/"+QString::number(id,10)+".xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), GET_LIST_MEMBERS_ID);
    issueGetRequest(req);
    
}
void Petrel::getListMemberships(qint64 cursor, quint64 list_id, quint64 id){

    QString requestStr("http://api.twitter.com/1/"+m_user+"/lists/memberships.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(cursor!=0) requestUrl.addQueryItem("cursor",QString::number(cursor,10));
    if(list_id!=0) requestUrl.addQueryItem("list_id",QString::number(list_id,10));
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), GET_LIST_MEMBERSHIPS);
    issueGetRequest(req);
    
}
void Petrel::getListStatuses(quint64 since_id, quint64 max_id, const QString& per_page, int page, quint64 list_id, quint64 id){

    QString requestStr("http://api.twitter.com/1/"+m_user+"/lists/"+QString::number(list_id,10)+"/statuses.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(per_page!="") requestUrl.addQueryItem("per_page",per_page);
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), GET_LIST_STATUSES);
    issueGetRequest(req);
    
}
void Petrel::getListSubscribers(quint64 list_id, qint64 cursor, quint64 id){

    QString requestStr("http://api.twitter.com/1/"+m_user+"/"+QString::number(list_id,10)+"/subscribers.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(cursor!=0) requestUrl.addQueryItem("cursor",QString::number(cursor,10));
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), GET_LIST_SUBSCRIBERS);
    issueGetRequest(req);
    
}
void Petrel::getListSubscribersId(const QString& user, quint64 list_id, quint64 id){

    QString requestStr("http://api.twitter.com/1/"+m_user+"/"+QString::number(list_id,10)+"/subscribers/"+QString::number(id,10)+".xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(user!="") requestUrl.addQueryItem("user",user);
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), GET_LIST_SUBSCRIBERS_ID);
    issueGetRequest(req);
    
}
void Petrel::getListSubscriptions(qint64 cursor, quint64 list_id, quint64 id){

    QString requestStr("http://api.twitter.com/1/"+m_user+"/lists/subscriptions.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(cursor!=0) requestUrl.addQueryItem("cursor",QString::number(cursor,10));
    if(list_id!=0) requestUrl.addQueryItem("list_id",QString::number(list_id,10));
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), GET_LIST_SUBSCRIPTIONS);
    issueGetRequest(req);
    
}
void Petrel::getLists(qint64 cursor, quint64 list_id, quint64 id){

    QString requestStr("http://api.twitter.com/1/"+m_user+"/lists.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(cursor!=0) requestUrl.addQueryItem("cursor",QString::number(cursor,10));
    if(list_id!=0) requestUrl.addQueryItem("list_id",QString::number(list_id,10));
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), GET_LISTS);
    issueGetRequest(req);
    
}
void Petrel::homeTimeline(quint64 since_id, quint64 max_id, int count, int page){

    QString requestStr("http://api.twitter.com/1/statuses/home_timeline.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), HOME_TIMELINE);
    issueGetRequest(req);
    
}
void Petrel::idsFollowers(qint64 cursor){

    QString requestStr("http://api.twitter.com/1/followers/ids.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(cursor!=0) requestUrl.addQueryItem("cursor",QString::number(cursor,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), IDS_FOLLOWERS);
    issueGetRequest(req);
    
}
void Petrel::idsFriends(qint64 cursor){

    QString requestStr("http://api.twitter.com/1/friends/ids.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(cursor!=0) requestUrl.addQueryItem("cursor",QString::number(cursor,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), IDS_FRIENDS);
    issueGetRequest(req);
    
}
void Petrel::leaveNotification(quint64 id, quint64 user_id, const QString& screen_name){

}
void Petrel::locationTrends(const QString& woeid){

    QString requestStr("http://api.twitter.com/1/trends/"+woeid+".xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), LOCATION_TRENDS);
    issueGetRequest(req);
    
}
void Petrel::mentions(quint64 since_id, quint64 max_id, int count, int page){

    QString requestStr("http://api.twitter.com/1/statuses/mentions.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), MENTIONS);
    issueGetRequest(req);
    
}
void Petrel::newDirectMessage(const QString& user, const QString& text){

}
void Petrel::postList(const QString& name, const QString& mode, const QString& description, quint64 list_id, quint64 id){

}
void Petrel::postListMember(quint64 list_id, quint64 id){

}
void Petrel::postListSubscriber(quint64 list_id, quint64 id){

}
void Petrel::postListsId(const QString& name, const QString& mode, const QString& description, quint64 list_id, quint64 id){

}
void Petrel::publicTimeline(){

    QString requestStr("http://api.twitter.com/1/statuses/public_timeline.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), PUBLIC_TIMELINE);
    issueGetRequest(req);
    
}
void Petrel::rateLimitStatus(){

    QString requestStr("http://api.twitter.com/1/account/rate_limit_status.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), RATE_LIMIT_STATUS);
    issueGetRequest(req);
    
}
void Petrel::reportSpam(quint64 id, quint64 user_id, const QString& screen_name){

}
void Petrel::retweet(quint64 id){

}
void Petrel::retweetedByMe(quint64 since_id, quint64 max_id, int count, int page){

    QString requestStr("http://api.twitter.com/1/statuses/retweeted_by_me.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), RETWEETED_BY_ME);
    issueGetRequest(req);
    
}
void Petrel::retweetedToMe(quint64 since_id, quint64 max_id, int count, int page){

    QString requestStr("http://api.twitter.com/1/statuses/retweeted_to_me.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), RETWEETED_TO_ME);
    issueGetRequest(req);
    
}
void Petrel::retweets(quint64 id, int count){

    QString requestStr("http://api.twitter.com/1/statuses/retweets/"+QString::number(id,10)+".xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), RETWEETS);
    issueGetRequest(req);
    
}
void Petrel::retweetsOfMe(quint64 since_id, quint64 max_id, int count, int page){

    QString requestStr("http://api.twitter.com/1/statuses/retweets_of_me.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), RETWEETS_OF_ME);
    issueGetRequest(req);
    
}
void Petrel::savedSearches(){

    QString requestStr("http://api.twitter.com/1/saved_searches.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), SAVED_SEARCHES);
    issueGetRequest(req);
    
}
void Petrel::searchUsers(const QString& q, const QString& per_page, int page){

    QString requestStr("http://api.twitter.com/1/users/search.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(q!="") requestUrl.addQueryItem("q",q);
    if(per_page!="") requestUrl.addQueryItem("per_page",per_page);
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), SEARCH_USERS);
    issueGetRequest(req);
    
}
void Petrel::sentDirectMessages(quint64 since_id, quint64 max_id, int count, int page){

    QString requestStr("http://api.twitter.com/1/direct_messages/sent.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), SENT_DIRECT_MESSAGES);
    issueGetRequest(req);
    
}
void Petrel::show(quint64 id){

    QString requestStr("http://api.twitter.com/1/statuses/show/"+QString::number(id,10)+".xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), SHOW);
    issueGetRequest(req);
    
}
void Petrel::showFriendships(quint64 source_id, const QString& source_screen_name, quint64 target_id, const QString& target_screen_name){

    QString requestStr("http://api.twitter.com/1/friendships/show.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(source_id!=0) requestUrl.addQueryItem("source_id",QString::number(source_id,10));
    if(source_screen_name!="") requestUrl.addQueryItem("source_screen_name",source_screen_name);
    if(target_id!=0) requestUrl.addQueryItem("target_id",QString::number(target_id,10));
    if(target_screen_name!="") requestUrl.addQueryItem("target_screen_name",target_screen_name);
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), SHOW_FRIENDSHIPS);
    issueGetRequest(req);
    
}
void Petrel::showSavedSearch(quint64 id){

    QString requestStr("http://api.twitter.com/1/saved_searches/show/"+QString::number(id,10)+".xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), SHOW_SAVED_SEARCH);
    issueGetRequest(req);
    
}
void Petrel::showUsers(quint64 id, quint64 user_id, const QString& screen_name){

    QString requestStr("http://api.twitter.com/1/users/show.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    if(user_id!=0) requestUrl.addQueryItem("user_id",QString::number(user_id,10));
    if(screen_name!="") requestUrl.addQueryItem("screen_name",screen_name);
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), SHOW_USERS);
    issueGetRequest(req);
    
}
void Petrel::testHelp(){

    QString requestStr("http://api.twitter.com/1/help/test.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), TEST_HELP);
    issueGetRequest(req);
    
}
void Petrel::update(const QString& status, quint64 in_reply_to_status_id, const QString& lat, const QString& long){

}
void Petrel::updateDeliveryDevice(const QString& device){

}
void Petrel::updateProfile(const QString& name, const QString& url, const QString& location, const QString& description){

}
void Petrel::updateProfileBackgroundImage(const QString& image, const QString& tile){

}
void Petrel::updateProfileColor(const QString& profile_background_color, const QString& profile_text_color, const QString& profile_link_color, const QString& profile_sidebar_fill_color, const QString& profile_sidebar_border_color){

}
void Petrel::updateProfileImage(const QString& image){

}
void Petrel::userTimeline(quint64 id, quint64 user_id, const QString& screen_name, quint64 since_id, quint64 max_id, int count, int page){

    QString requestStr("http://api.twitter.com/1/statuses/user_timeline.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem
    if(id!=0) requestUrl.addQueryItem("id",QString::number(id,10));
    if(user_id!=0) requestUrl.addQueryItem("user_id",QString::number(user_id,10));
    if(screen_name!="") requestUrl.addQueryItem("screen_name",screen_name);
    if(since_id!=0) requestUrl.addQueryItem("since_id",QString::number(since_id,10));
    if(max_id!=0) requestUrl.addQueryItem("max_id",QString::number(max_id,10));
    if(count!=0) requestUrl.addQueryItem("count",QString::number(count,10));
    if(page!=0) requestUrl.addQueryItem("page",QString::number(page,10));
    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), USER_TIMELINE);
    issueGetRequest(req);
    
}
void Petrel::verifyCredentials(){

    QString requestStr("http://api.twitter.com/1/account/verify_credentials.xml");
    QUrl requestUrl(requestStr);
    //addQueryItem

    QNetworkRequest req(requestUrl);
    req.setAttribute((QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE), VERIFY_CREDENTIALS);
    issueGetRequest(req);
    
}

//END autogenerated methods

void Petrel::replyFinished(QNetworkReply *reply)
{
    QNetworkRequest request = reply->request();
    QString replyStr( reply->readAll() );
    int role = request.attribute( (QNetworkRequest::Attribute)(QNetworkRequest::User + ATTR_ROLE) ).toInt();
    QDomDocument doc;
    doc.setContent(replyStr);
    switch(role){
        //autogenerated choice
        case AVAILABLE_TRENDS:
        {
          locations_t l(doc.documentElement());
          emit availableTrendsReceived(l);
          break;
        }
        case BLOCKING_IDS_BLOCKS:
        {
          ids_t i(doc.documentElement());
          emit blocking_IdsBlocksReceived(i);
          break;
        }
        case CREATE_BLOCK:
        {
          user_t u(doc.documentElement());
          emit createBlockReceived(u);
          break;
        }
        case CREATE_FAVORITE:
        {
          status_t s(doc.documentElement());
          emit createFavoriteReceived(s);
          break;
        }
        case CREATE_FRIENDSHIP:
        {
          user_t u(doc.documentElement());
          emit createFriendshipReceived(u);
          break;
        }
        case CREATE_SAVED_SEARCH:
        {
          saved_search_t s(doc.documentElement());
          emit createSavedSearchReceived(s);
          break;
        }
        case DELETE_LIST_ID:
        {
          list_t l(doc.documentElement());
          emit deleteListIdReceived(l);
          break;
        }
        case DELETE_LIST_MEMBER:
        {
          list_t l(doc.documentElement());
          emit deleteListMemberReceived(l);
          break;
        }
        case DELETE_LIST_SUBSCRIBER:
        {
          list_t l(doc.documentElement());
          emit deleteListSubscriberReceived(l);
          break;
        }
        case DESTROY:
        {
          status_t s(doc.documentElement());
          emit destroyReceived(s);
          break;
        }
        case DESTROY_BLOCK:
        {
          user_t u(doc.documentElement());
          emit destroyBlockReceived(u);
          break;
        }
        case DESTROY_DIRECT_MESSAGE:
        {
          direct_message_t d(doc.documentElement());
          emit destroyDirectMessageReceived(d);
          break;
        }
        case DESTROY_FAVORITE:
        {
          status_t s(doc.documentElement());
          emit destroyFavoriteReceived(s);
          break;
        }
        case DESTROY_FRIENDSHIP:
        {
          user_t u(doc.documentElement());
          emit destroyFriendshipReceived(u);
          break;
        }
        case DESTROY_SAVED_SEARCH:
        {
          saved_search_t s(doc.documentElement());
          emit destroySavedSearchReceived(s);
          break;
        }
        case DIRECT_MESSAGES:
        {
          direct_messages_t d(doc.documentElement());
          emit directMessagesReceived(d);
          break;
        }
        case EXISTS_FRIENDSHIPS:
        {
          friends_t f(doc.documentElement());
          emit existsFriendshipsReceived(f);
          break;
        }
        case FAVORITES:
        {
          statuses_t s(doc.documentElement());
          emit favoritesReceived(s);
          break;
        }
        case FOLLOW_NOTIFICATION:
        {
          user_t u(doc.documentElement());
          emit followNotificationReceived(u);
          break;
        }
        case FOLLOWERS:
        {
          users_t u(doc.documentElement());
          emit followersReceived(u);
          break;
        }
        case FRIENDS:
        {
          users_t u(doc.documentElement());
          emit friendsReceived(u);
          break;
        }
        case FRIENDS_TIMELINE:
        {
          statuses_t s(doc.documentElement());
          emit friendsTimelineReceived(s);
          break;
        }
        case GET_LIST_ID:
        {
          list_t l(doc.documentElement());
          emit getListIdReceived(l);
          break;
        }
        case GET_LIST_MEMBERS:
        {
          users_list_t u(doc.documentElement());
          emit getListMembersReceived(u);
          break;
        }
        case GET_LIST_MEMBERS_ID:
        {
          user_t u(doc.documentElement());
          emit getListMembersIdReceived(u);
          break;
        }
        case GET_LIST_MEMBERSHIPS:
        {
          lists_list_t l(doc.documentElement());
          emit getListMembershipsReceived(l);
          break;
        }
        case GET_LIST_STATUSES:
        {
          statuses_t s(doc.documentElement());
          emit getListStatusesReceived(s);
          break;
        }
        case GET_LIST_SUBSCRIBERS:
        {
          users_list_t u(doc.documentElement());
          emit getListSubscribersReceived(u);
          break;
        }
        case GET_LIST_SUBSCRIBERS_ID:
        {
          user_t u(doc.documentElement());
          emit getListSubscribersIdReceived(u);
          break;
        }
        case GET_LIST_SUBSCRIPTIONS:
        {
          lists_list_t l(doc.documentElement());
          emit getListSubscriptionsReceived(l);
          break;
        }
        case GET_LISTS:
        {
          lists_list_t l(doc.documentElement());
          emit getListsReceived(l);
          break;
        }
        case HOME_TIMELINE:
        {
          statuses_t s(doc.documentElement());
          emit homeTimelineReceived(s);
          break;
        }
        case IDS_FOLLOWERS:
        {
          id_list_t i(doc.documentElement());
          emit idsFollowersReceived(i);
          break;
        }
        case IDS_FRIENDS:
        {
          id_list_t i(doc.documentElement());
          emit idsFriendsReceived(i);
          break;
        }
        case LEAVE_NOTIFICATION:
        {
          user_t u(doc.documentElement());
          emit leaveNotificationReceived(u);
          break;
        }
        case LOCATION_TRENDS:
        {
          matching_trends_t m(doc.documentElement());
          emit locationTrendsReceived(m);
          break;
        }
        case MENTIONS:
        {
          statuses_t s(doc.documentElement());
          emit mentionsReceived(s);
          break;
        }
        case NEW_DIRECT_MESSAGE:
        {
          direct_message_t d(doc.documentElement());
          emit newDirectMessageReceived(d);
          break;
        }
        case POST_LIST:
        {
          list_t l(doc.documentElement());
          emit postListReceived(l);
          break;
        }
        case POST_LIST_MEMBER:
        {
          list_t l(doc.documentElement());
          emit postListMemberReceived(l);
          break;
        }
        case POST_LIST_SUBSCRIBER:
        {
          list_t l(doc.documentElement());
          emit postListSubscriberReceived(l);
          break;
        }
        case POST_LISTS_ID:
        {
          list_t l(doc.documentElement());
          emit postListsIdReceived(l);
          break;
        }
        case PUBLIC_TIMELINE:
        {
          statuses_t s(doc.documentElement());
          emit publicTimelineReceived(s);
          break;
        }
        case RATE_LIMIT_STATUS:
        {
          hash_t h(doc.documentElement());
          emit rateLimitStatusReceived(h);
          break;
        }
        case REPORT_SPAM:
        {
          user_t u(doc.documentElement());
          emit reportSpamReceived(u);
          break;
        }
        case RETWEET:
        {
          status_t s(doc.documentElement());
          emit retweetReceived(s);
          break;
        }
        case RETWEETED_BY_ME:
        {
          statuses_t s(doc.documentElement());
          emit retweetedByMeReceived(s);
          break;
        }
        case RETWEETED_TO_ME:
        {
          statuses_t s(doc.documentElement());
          emit retweetedToMeReceived(s);
          break;
        }
        case RETWEETS:
        {
          statuses_t s(doc.documentElement());
          emit retweetsReceived(s);
          break;
        }
        case RETWEETS_OF_ME:
        {
          statuses_t s(doc.documentElement());
          emit retweetsOfMeReceived(s);
          break;
        }
        case SAVED_SEARCHES:
        {
          saved_searches_t s(doc.documentElement());
          emit savedSearchesReceived(s);
          break;
        }
        case SEARCH_USERS:
        {
          users_t u(doc.documentElement());
          emit searchUsersReceived(u);
          break;
        }
        case SENT_DIRECT_MESSAGES:
        {
          direct_messages_t d(doc.documentElement());
          emit sentDirectMessagesReceived(d);
          break;
        }
        case SHOW:
        {
          status_t s(doc.documentElement());
          emit showReceived(s);
          break;
        }
        case SHOW_FRIENDSHIPS:
        {
          relationship_t r(doc.documentElement());
          emit showFriendshipsReceived(r);
          break;
        }
        case SHOW_SAVED_SEARCH:
        {
          saved_search_t s(doc.documentElement());
          emit showSavedSearchReceived(s);
          break;
        }
        case SHOW_USERS:
        {
          user_t u(doc.documentElement());
          emit showUsersReceived(u);
          break;
        }
        case TEST_HELP:
        {
          ok_t o(doc.documentElement());
          emit testHelpReceived(o);
          break;
        }
        case UPDATE:
        {
          status_t s(doc.documentElement());
          emit updateReceived(s);
          break;
        }
        case UPDATE_DELIVERY_DEVICE:
        {
          user_t u(doc.documentElement());
          emit updateDeliveryDeviceReceived(u);
          break;
        }
        case UPDATE_PROFILE:
        {
          user_t u(doc.documentElement());
          emit updateProfileReceived(u);
          break;
        }
        case UPDATE_PROFILE_BACKGROUND_IMAGE:
        {
          user_t u(doc.documentElement());
          emit updateProfileBackgroundImageReceived(u);
          break;
        }
        case UPDATE_PROFILE_COLOR:
        {
          user_t u(doc.documentElement());
          emit updateProfileColorReceived(u);
          break;
        }
        case UPDATE_PROFILE_IMAGE:
        {
          user_t u(doc.documentElement());
          emit updateProfileImageReceived(u);
          break;
        }
        case USER_TIMELINE:
        {
          statuses_t s(doc.documentElement());
          emit userTimelineReceived(s);
          break;
        }
        case VERIFY_CREDENTIALS:
        {
          user_t u(doc.documentElement());
          emit verifyCredentialsReceived(u);
          break;
        }

    }
    reply->deleteLater();
}
