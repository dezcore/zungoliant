#ifndef YFIELDS_H_
#define YFIELDS_H_

#define URLS_FILE "/data/file/urls"
#define DOWNLOAD_FILE "/data/file/download"
#define YINITDATA_FILE_PATH "/data/file/ytInitialData"
#define YRESULTS_FIELDS  "/contents/twoColumnWatchNextResults/secondaryResults/secondaryResults/results"

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
#define VIDEO_PAGE_DESCRIPTION_FIELD "/contents/1/videoSecondaryInfoRenderer/attributedDescription/content"
#define VIDEO_VIEWCOUNT_FIELD "/contents/0/videoPrimaryInfoRenderer/viewCount/videoViewCountRenderer/viewCount/simpleText"
#define VIDEO_VIEWCOUNT_SHORT_FIELD "/contents/0/videoPrimaryInfoRenderer/viewCount/videoViewCountRenderer/shortViewCount/simpleText"

#define VIDEO_PAGE_CHANNEL_TITLE_FIELD "/contents/1/videoSecondaryInfoRenderer/owner/videoOwnerRenderer/title/runs/0/text"
#define VIDEO_PAGE_CHANNEL_IMG_FIELD "/contents/1/videoSecondaryInfoRenderer/owner/videoOwnerRenderer/thumbnail/thumbnails/0/url"
#define VIDEO_PAGE_CHANNEL_URL_FIELD "/contents/1/videoSecondaryInfoRenderer/owner/videoOwnerRenderer/title/runs/0/navigationEndpoint/commandMetadata/webCommandMetadata/url"

//CHANNEL PAGE
#define CHANNEL_PAGE_ROOT_FIELD "/contents/twoColumnBrowseResultsRenderer"
#define CHANNEL_PAGE_HOME_TAB_FIELD "/0/tabRenderer/endpoint/commandMetadata/webCommandMetadata/url"
#define CHANNEL_PAGE_HOME_TAB_CONTENT_FIELD "/0/tabRenderer/content/sectionListRenderer/contents"

//Channe Page
//-> /0/itemSectionRenderer/contents/0/channelVideoPlayerRenderer/videoId
//-> /0/itemSectionRenderer/contents/0/channelVideoPlayerRenderer/title/runs/0/text
//-> /0/itemSectionRenderer/contents/0/channelVideoPlayerRenderer/description/runs/0/text
//-> /0/itemSectionRenderer/contents/0/channelVideoPlayerRenderer/viewCountText/simpleText
//-> /0/itemSectionRenderer/contents/0/channelVideoPlayerRenderer/readMoreText/runs/0/navigationEndpoint/commandMetadata/webCommandMetadata/url

#define VIDEOS_TAB_FIELD "/contents/twoColumnBrowseResultsRenderer/1/tabRenderer/endpoint/commandMetadata/webCommandMetadata/url"
#define PLAYLISTS_TAB_FIELD "/contents/twoColumnBrowseResultsRenderer/4/tabRenderer/endpoint/commandMetadata/webCommandMetadata/url"
#define CHANNELS_TAB_FIELD "/contents/twoColumnBrowseResultsRenderer/6/tabRenderer/endpoint/commandMetadata/webCommandMetadata/url"
#define TAGS_FIELD "/microformat/microformatDataRenderer/tags"

//Youtube Page
#define YOUTBE_VIDEOS_FIELD "/contents/twoColumnBrowseResultsRenderer/tabs/0/tabRenderer/content/richGridRenderer/contents"
//-> /0/richItemRenderer/content/videoRenderer/videoId
//-> /0/richItemRenderer/content/videoRenderer/thumbnail/thumbnails/0/url
//-> /0/richItemRenderer/content/videoRenderer/title/runs/0/text
//-> /0/richItemRenderer/content/videoRenderer/descriptionSnippet/runs/0/text
//-> /0/richItemRenderer/content/videoRenderer/navigationEndpoint/commandMetadata/webCommandMetadata/url

#endif