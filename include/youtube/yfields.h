#ifndef YFIELDS_H_
#define YFIELDS_H_

#define URLS_FILE "/data/file/urls"
#define DOWNLOAD_FILE "/data/file/download"
#define YINITDATA_FILE_PATH "/data/file/ytInitialData"
#define YRESULTS_FIELDS  "/contents/twoColumnWatchNextResults/secondaryResults/secondaryResults/results"

//URL regex
//(https?|www)[^ ]+ 
//Youtube
#define YOUTUBE_ROOT_URL "https://www.youtube.com/watch"
#define YOUTUBE_WATCH_URI "/watch?v="

//VIDEO PAGE
#define VIDEO_PAGE_CHANNEL_ROOT_FIELD "/contents/twoColumnWatchNextResults/results/results"
#define VIDEO_PAGE_ROOT_FIELD "/contents/twoColumnWatchNextResults/secondaryResults/secondaryResults/results"

#define VIDEO_PAGE_PLAYLIST_ITEM_VIDEOID_FIELD "/compactVideoRenderer/videoId"
#define VIDEO_PAGE_PLAYLIST_ITEM_TITLE_FIELD "/compactVideoRenderer/title/simpleText"
#define VIDEO_PAGE_PLAYLIST_ITEM_LENGTH_FIELD "/compactVideoRenderer/lengthText/simpleText"
#define VIDEO_PAGE_PLAYLIST_ITEM_IMG_FIELD "/compactVideoRenderer/thumbnail/thumbnails/0/url"
#define VIDEO_PAGE_PLAYLIST_ITEM_VIEW_COUNT_FIELD "/compactVideoRenderer/viewCountText/simpleText"
#define VIDEO_PAGE_PLAYLIST_ITEM_URL_FIELD "/compactVideoRenderer/navigationEndpoint/commandMetadata/webCommandMetadata/url"

#define VIDEO_PAGE_TITLE_FIELD "/contents/0/videoPrimaryInfoRenderer/title/runs/0/text"
#define VIDEO_PAGE_DATE_FIELD "/contents/0/videoPrimaryInfoRenderer/dateText/simpleText"
#define VIDEO_PAGE_DESCRIPTION_FIELD "/contents/1/videoSecondaryInfoRenderer/attributedDescription/content"
#define VIDEO_VIEWCOUNT_FIELD "/contents/0/videoPrimaryInfoRenderer/viewCount/videoViewCountRenderer/viewCount/simpleText"
#define VIDEO_VIEWCOUNT_SHORT_FIELD "/contents/0/videoPrimaryInfoRenderer/viewCount/videoViewCountRenderer/shortViewCount/simpleText"

#define VIDEO_PAGE_CHANNEL_TITLE_FIELD "/contents/1/videoSecondaryInfoRenderer/owner/videoOwnerRenderer/title/runs/0/text"
#define VIDEO_PAGE_CHANNEL_IMG_FIELD "/contents/1/videoSecondaryInfoRenderer/owner/videoOwnerRenderer/thumbnail/thumbnails/0/url"
#define VIDEO_PAGE_CHANNEL_URL_FIELD "/contents/1/videoSecondaryInfoRenderer/owner/videoOwnerRenderer/title/runs/0/navigationEndpoint/commandMetadata/webCommandMetadata/url"

//CHANNEL PAGE
#define CHANNEL_PAGE_ROOT_FIELD "/twoColumnBrowseResultsRenderer"
#define CHANNEL_PAGE_TABS_FIELD "/tabs"
#define CHANNEL_PAGE_HOME_TAB_URL_FIELD "/tabRenderer/endpoint/commandMetadata/webCommandMetadata/url"
#define CHANNEL_PAGE_HOME_TAB_CONTENTS_FIELD "/tabRenderer/content/sectionListRenderer/contents"
#define CHANNEL_PAGE_VIDEOS_TAB_CONTENTS_FIELD "/tabRenderer/content/richGridRenderer/contents"
#define CHANNELS_PAGE_TAB_CONTENTS_FIELD "/tabRenderer/content/sectionListRenderer/contents/0/itemSectionRenderer/contents/0/gridRenderer/items"

#define CHANNEL_PAGE_HOME_VIDEOID_FIELD "/itemSectionRenderer/contents/0/channelVideoPlayerRenderer/videoId"
#define CHANNEL_PAGE_HOME_VIDEO_TITLE_FIELD "/itemSectionRenderer/contents/0/channelVideoPlayerRenderer/title/runs/0/text"
#define CHANNEL_PAGE_HOME_VIDEO_DESCRIPTION_FIELD "/itemSectionRenderer/contents/0/channelVideoPlayerRenderer/description/runs/0/text"
#define CHANNEL_PAGE_HOME_VIDEO_VIEWCOUNT_FIELD "itemSectionRenderer/contents/0/channelVideoPlayerRenderer/viewCountText/simpleText"
#define CHANNEL_PAGE_HOME_VIDEO_URL_FIELD "/itemSectionRenderer/contents/0/channelVideoPlayerRenderer/readMoreText/runs/0/navigationEndpoint/commandMetadata/webCommandMetadata/url"

#define VIDEOS_PAGE_VIDEOID_FIELD "/richItemRenderer/content/videoRenderer/videoId"
#define VIDEOS_PAGE_VIDEO_TITLE_FIELD "/richItemRenderer/content/videoRenderer/title/runs/0/text"
#define VIDEOS_PAGE_VIDEO_DESCRIPTION_FIELD "/richItemRenderer/content/videoRenderer/descriptionSnippet/runs/0/text"
#define VIDEOS_PAGE_VIDEO_VIEWCOUNT_FIELD "/richItemRenderer/content/videoRenderer/viewCountText/simpleText"
#define VIDEOS_PAGE_VIDEO_URL_FIELD "/richItemRenderer/content/videoRenderer/navigationEndpoint/commandMetadata/webCommandMetadata/url"

#define CHANNELS_PAGE_ITEM_CHANNELID_FIELD "/gridChannelRenderer/channelId"
#define CHANNELS_PAGE_ITEM_CHANNELIMG_FIELD "/gridChannelRenderer/thumbnail/thumbnails/0/url"
#define CHANNELS_PAGE_ITEM_CHANNELTITLE_FIELD "/gridChannelRenderer/title/simpleText"
#define CHANNELS_PAGE_ITEM_CHANNELSUBSCRIBERCOUNT_FIELD "/gridChannelRenderer/subscriberCountText/simpleText"
#define CHANNELS_PAGE_ITEM_CHANNELURL_FIELD "/gridChannelRenderer/navigationEndpoint/commandMetadata/webCommandMetadata/url"

#define CHANNEL_PAGE_HOME_ITEM_VIDEOID_FIELD "/itemSectionRenderer/contents/0/shelfRenderer/content/horizontalListRenderer/items/0/gridVideoRenderer/videoId"
#define CHANNEL_PAGE_HOME_ITEM_IMG_FIELD "/itemSectionRenderer/contents/0/shelfRenderer/content/horizontalListRenderer/items/0/gridVideoRenderer/thumbnail/thumbnails/0/url"
#define CHANNEL_PAGE_HOME_ITEM_VIDEO_TITLE_FIELD "/itemSectionRenderer/contents/0/shelfRenderer/content/horizontalListRenderer/items/0/gridVideoRenderer/title/simpleText"
#define CHANNEL_PAGE_HOME_ITEM_VIDEO_DESCRIPTION_FIELD "/itemSectionRenderer/contents/0/shelfRenderer/description/runs/0/text"
#define CHANNEL_PAGE_HOME_ITEM_VIDEO_VIEWCOUNT_FIELD "/itemSectionRenderer/contents/0/shelfRenderer/content/horizontalListRenderer/items/0/gridVideoRenderer/viewCountText/simpleText"
#define CHANNEL_PAGE_HOME_ITEM_VIDEO_URL_FIELD "/itemSectionRenderer/contents/0/shelfRenderer/content/horizontalListRenderer/items/0/gridVideoRenderer/navigationEndpoint/commandMetadata/webCommandMetadata/url"

#define VIDEOS_TAB_FIELD "/contents/twoColumnBrowseResultsRenderer/1/tabRenderer/endpoint/commandMetadata/webCommandMetadata/url"
#define PLAYLISTS_TAB_FIELD "/contents/twoColumnBrowseResultsRenderer/4/tabRenderer/endpoint/commandMetadata/webCommandMetadata/url"
#define CHANNELS_TAB_FIELD "/contents/twoColumnBrowseResultsRenderer/6/tabRenderer/endpoint/commandMetadata/webCommandMetadata/url"
#define TAGS_FIELD "/microformat/microformatDataRenderer/tags"

//Youtube Page
#define YOUTBE_VIDEOS_FIELD "/contents/twoColumnBrowseResultsRenderer/tabs/0/tabRenderer/content/richGridRenderer/contents"

//PlayList (VIDEO)
#define VIDEOID_FIELD "/compactVideoRenderer/videoId"
#define TITLE_FIELD "/compactVideoRenderer/title/simpleText"
#define LENGTH_FIELD "/compactVideoRenderer/lengthText/simpleText"
#define IMG_FIELD "/compactVideoRenderer/thumbnail/thumbnails/0/url"
#define VIEW_COUNT_FIELD "/compactVideoRenderer/viewCountText/simpleText"
#define URL_FIELD "/compactVideoRenderer/navigationEndpoint/commandMetadata/webCommandMetadata/url"

#endif