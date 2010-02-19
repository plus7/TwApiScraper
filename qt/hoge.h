#include <QtCore>
#include <QtXml>

QUrl getUrlValue(QDomElement& elm){
  return QUrl(getStrValue(elm));
}

bool getBoolValue(QDomElement& elm){
  if(getStrValue(elm)=="true"){
    return true;
  }else{
    return false;
  }
}

quint64 getUInt64Value(QDomElement& elm){
  QString str = getStrValue(elm);
  bool ok;
  quint64 dec = str.toULongLong(&ok, 10);
  if(ok)
    return dec;
  else
    return 0;
}

QString getStrValue(QDomElement& elm){
  QDomNode child = elm.firstChild();
  if(child.isNull())
    return "";
  else
    return child.nodeValue();
}

QDateTime getDateTimeValue(QDomElement& elm){
  return QDateTime::fromString(getStrValue(elm));
}

Color getColorValue(QDomElement& elm){
  return Color(getStrValue(elm));
}

class sender_t {
  sender_t(QDomElement& element){   
    QDomElement child = element.firstChildElement();
    for (; !child.isNull(); child = child.nextSiblingElement()) {
    if(tagName == "id"){
      id = getUInt64Value(child);
    }else if(tagName == "verified"){
      verified = getBoolValue(child);
    }else if(tagName == "profile_sidebar_fill_color"){
      profile_sidebar_fill_color = getColorValue(child);
    }else if(tagName == "location"){
      location = getStrValue(child);
    }else if(tagName == "profile_image_url"){
      profile_image_url = getUrlValue(child);
    }else if(tagName == "created_at"){
      created_at = getDateTimeValue(child);
    }else if(tagName == "hogehoge"){
      hogehoge = hogehoge_t(child);
    }else if(tagName == "pluralElm"){
      pluralElm.append(hogehoge_t(child));
    }
  }
  quint64 id;
  bool verified;
  ColorString profile_sidebar_fill_color;
  ColorString profile_text_color;
  quint64 followers_count;
  bool protected;
  QString location;
  ColorString profile_background_color;
  int utc_offset;
  quint64 statuses_count;
  QString description;
  quint64 friends_count;
  ColorString profile_link_color;
  QUrl profile_image_url;
  bool notifications;
  QUrl profile_background_image_url;
  QString screen_name;
  bool profile_background_tile;
  quint64 favourites_count;
  QString name;
  QUrl url;
  QDateTime created_at;
  QString time_zone;
  ColorString profile_sidebar_border_color;
  bool following;
};

class hash_t {
  QString remaining_hits;
  QString hourly_limit;
  QString reset_time_in_seconds;
  QString reset_time;
};

class target_t {
  bool following;
  QString notifications_enabled;
  bool followed_by;
  quint64 id;
  QString screen_name;
};

class geo_t {
  QString georss:point;
};

class recipient_t {
  quint64 id;
  bool verified;
  ColorString profile_sidebar_fill_color;
  ColorString profile_text_color;
  quint64 followers_count;
  bool protected;
  QString location;
  ColorString profile_background_color;
  int utc_offset;
  quint64 statuses_count;
  QString description;
  quint64 friends_count;
  ColorString profile_link_color;
  QUrl profile_image_url;
  bool notifications;
  QUrl profile_background_image_url;
  QString screen_name;
  bool profile_background_tile;
  quint64 favourites_count;
  QString name;
  QUrl url;
  QDateTime created_at;
  QString time_zone;
  ColorString profile_sidebar_border_color;
  bool following;
};

class locations_t {
  QList<QString> location;
};

class saved_search_t {
  QString query;
  QDateTime created_at;
  int position;
  quint64 id;
  QString name;
};

class ids_t {
  QList<quint64> id;
};

//----------
class retweeted_status_t {
  bool favorited;
  bool truncated;
  QString text;
  QDateTime created_at;
  QString source;
  quint64 in_reply_to_status_id;
  QString in_reply_to_screen_name;
  quint64 in_reply_to_user_id;
  geo_t geo;
  quint64 id;
  user_t user;
};

class trends_t {
  QString trend;
  locations_t locations;
};

//----------
class status_t {
  bool favorited;
  QString contributors;
  retweeted_status_t retweeted_status;
  bool truncated;
  QString text;
  QDateTime created_at;
  QString source;
  quint64 in_reply_to_status_id;
  QString in_reply_to_screen_name;
  quint64 in_reply_to_user_id;
  geo_t geo;
  quint64 id;
  user_t user;
};

class saved_searches_t {
  QList<saved_search_t> saved_search;
};

class relationship_t {
  QString source;
  target_t target;
};

class retweeted_status_t {
  bool favorited;
  bool truncated;
  QString text;
  QDateTime created_at;
  QString source;
  quint64 in_reply_to_status_id;
  QString in_reply_to_screen_name;
  quint64 in_reply_to_user_id;
  geo_t geo;
  quint64 id;
  user_t user;
};

class direct_message_t {
  sender_t sender;
  QString text;
  QString sender_screen_name;
  quint64 sender_id;
  quint64 id;
  quint64 recipient_id;
  QString recipient_screen_name;
  recipient_t recipient;
  QDateTime created_at;
};

class id_list_t {
  QString previous_cursor;
  QString next_cursor;
  ids_t ids;
};

class trends_t {
  QString trend;
  locations_t locations;
};

class user_t {
  quint64 id;
  bool verified;
  ColorString profile_sidebar_fill_color;
  ColorString profile_text_color;
  quint64 followers_count;
  bool protected;
  QString location;
  ColorString profile_background_color;
  status_t status;
  int utc_offset;
  quint64 statuses_count;
  QString description;
  quint64 friends_count;
  ColorString profile_link_color;
  QUrl profile_image_url;
  bool notifications;
  bool geo_enabled;
  QUrl profile_background_image_url;
  QString screen_name;
  QString lang;
  bool profile_background_tile;
  quint64 favourites_count;
  QString name;
  QUrl url;
  QDateTime created_at;
  bool contributors_enabled;
  QString time_zone;
  ColorString profile_sidebar_border_color;
  bool following;
};

class users_t {
  QList<user_t> user;
};

class matching_trends_t {
  trends_t trends;
};

class statuses_t {
  QList<status_t> status;
};

class direct_messages_t {
  QList<direct_message_t> direct_message;
};
