#include "MediaConfig.h"

using namespace webserv;
using namespace webserv::config;

MediaConfig::MediaConfig()
{
	_fileExtensionToMediaType[".html"] = "text/html";
	_fileExtensionToMediaType[".htm"] = "text/html";
	_fileExtensionToMediaType[".shtml"] = "text/html";
	_fileExtensionToMediaType[".css"] = "text/css";
	_fileExtensionToMediaType[".xml"] = "text/xml";
	_fileExtensionToMediaType[".gif"] = "image/gif";
	_fileExtensionToMediaType[".jpeg"] = "image/jpeg";
	_fileExtensionToMediaType[".jpg"] = "image/jpeg";
	_fileExtensionToMediaType[".js"] = "application/javascript";
	_fileExtensionToMediaType[".atom"] = "application/atom+xml";
	_fileExtensionToMediaType[".rss"] = "application/rss+xml";

	_fileExtensionToMediaType[".mml"] = "text/mathml";
	_fileExtensionToMediaType[".txt"] = "text/plain";
	_fileExtensionToMediaType[".jad"] = "text/vnd.sun.j2me.app-descriptor";
	_fileExtensionToMediaType[".wml"] = "text/vnd.wap.wml";
	_fileExtensionToMediaType[".htc"] = "text/x-component";

	_fileExtensionToMediaType[".png"] = "image/png";
	_fileExtensionToMediaType[".svg"] = "image/svg+xml";
	_fileExtensionToMediaType[".svgz"] = "image/svg+xml";
	_fileExtensionToMediaType[".tif"] = "image/tiff";
	_fileExtensionToMediaType[".tiff"] = "image/tiff";
	_fileExtensionToMediaType[".wbmp"] = "image/vnd.wap.wbmp";
	_fileExtensionToMediaType[".webp"] = "image/webp";
	_fileExtensionToMediaType[".ico"] = "image/x-icon";
	_fileExtensionToMediaType[".jng"] = "image/x-jng";
	_fileExtensionToMediaType[".bmp"] = "image/x-ms-bmp";

	_fileExtensionToMediaType[".woff"] = "font/woff";
	_fileExtensionToMediaType[".woff2"] = "font/woff2";

	_fileExtensionToMediaType[".jar"] = "application/java-archive";
	_fileExtensionToMediaType[".war"] = "application/java-archive";
	_fileExtensionToMediaType[".ear"] = "application/java-archive";
	_fileExtensionToMediaType[".json"] = "application/json";
	_fileExtensionToMediaType[".hqx"] = "application/mac-binhex40";
	_fileExtensionToMediaType[".doc"] = "application/msword";
	_fileExtensionToMediaType[".pdf"] = "application/pdf";
	_fileExtensionToMediaType[".ps"] = "application/postscript";
	_fileExtensionToMediaType[".eps"] = "application/postscript";
	_fileExtensionToMediaType[".ai"] = "application/postscript";
	_fileExtensionToMediaType[".rtf"] = "application/rtf";
	_fileExtensionToMediaType[".m3u8"] = "application/vnd.apple.mpegurl";
	_fileExtensionToMediaType[".kml"] = "application/vnd.google-earth.kml+xml";
	_fileExtensionToMediaType[".kmz"] = "application/vnd.google-earth.kmz";
	_fileExtensionToMediaType[".xls"] = "application/vnd.ms-excel";
	_fileExtensionToMediaType[".eot"] = "application/vnd.ms-fontobject";
	_fileExtensionToMediaType[".ppt"] = "application/vnd.ms-powerpoint";
	_fileExtensionToMediaType[".odg"] = "application/vnd.oasis.opendocument.graphics";
	_fileExtensionToMediaType[".odp"] = "application/vnd.oasis.opendocument.presentation";
	_fileExtensionToMediaType[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
	_fileExtensionToMediaType[".odt"] = "application/vnd.oasis.opendocument.text";

	_fileExtensionToMediaType[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	_fileExtensionToMediaType[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	_fileExtensionToMediaType[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";

	_fileExtensionToMediaType[".wmlc"] = "application/vnd.wap.wmlc";
	_fileExtensionToMediaType[".7z"] = "application/x-7z-compressed";
	_fileExtensionToMediaType[".cco"] = "application/x-cocoa";
	_fileExtensionToMediaType[".jardiff"] = "application/x-java-archive-diff";
	_fileExtensionToMediaType[".jnlp"] = "application/x-java-jnlp-file";
	_fileExtensionToMediaType[".run"] = "application/x-makeself";
	_fileExtensionToMediaType[".pl"] = "application/x-perl";
	_fileExtensionToMediaType[".pm"] = "application/x-perl";
	_fileExtensionToMediaType[".prc"] = "application/x-pilot";
	_fileExtensionToMediaType[".pdb"] = "application/x-pilot";
	_fileExtensionToMediaType[".rar"] = "application/x-rar-compressed";
	_fileExtensionToMediaType[".rpm"] = "application/x-redhat-package-manager";
	_fileExtensionToMediaType[".sea"] = "application/x-sea";
	_fileExtensionToMediaType[".swf"] = "application/x-shockwave-flash";
	_fileExtensionToMediaType[".sit"] = "application/x-stuffit";
	_fileExtensionToMediaType[".tcl"] = "application/x-tcl";
	_fileExtensionToMediaType[".tk"] = "application/x-tcl";
	_fileExtensionToMediaType[".der"] = "application/x-x509-ca-cert";
	_fileExtensionToMediaType[".pem"] = "application/x-x509-ca-cert";
	_fileExtensionToMediaType[".crt"] = "application/x-x509-ca-cert";
	_fileExtensionToMediaType[".xpi"] = "application/x-xpinstall";
	_fileExtensionToMediaType[".xhtml"] = "application/xhtml+xml";
	_fileExtensionToMediaType[".xspf"] = "application/xspf+xml";
	_fileExtensionToMediaType[".zip"] = "application/zip";

	_fileExtensionToMediaType[".bin"] = "application/octet-stream";
	_fileExtensionToMediaType[".exe"] = "application/octet-stream";
	_fileExtensionToMediaType[".dll"] = "application/octet-stream";
	_fileExtensionToMediaType[".deb"] = "application/octet-stream";
	_fileExtensionToMediaType[".dmg"] = "application/octet-stream";
	_fileExtensionToMediaType[".iso"] = "application/octet-stream";
	_fileExtensionToMediaType[".img"] = "application/octet-stream";
	_fileExtensionToMediaType[".msi"] = "application/octet-stream";
	_fileExtensionToMediaType[".msp"] = "application/octet-stream";
	_fileExtensionToMediaType[".msm"] = "application/octet-stream";

	_fileExtensionToMediaType[".mid"] = "audio/midi";
	_fileExtensionToMediaType[".midi"] = "audio/midi";
	_fileExtensionToMediaType[".kar"] = "audio/midi";
	_fileExtensionToMediaType[".mp3"] = "audio/mpeg";
	_fileExtensionToMediaType[".ogg"] = "audio/ogg";
	_fileExtensionToMediaType[".m4a"] = "audio/x-m4a";
	_fileExtensionToMediaType[".ra"] = "audio/x-realaudio";

	_fileExtensionToMediaType[".3gpp"] = "video/3gpp";
	_fileExtensionToMediaType[".3gp"] = "video/3gpp";
	_fileExtensionToMediaType[".ts"] = "video/mp2t";
	_fileExtensionToMediaType[".mp4"] = "video/mp4";
	_fileExtensionToMediaType[".mpeg"] = "video/mpeg";
	_fileExtensionToMediaType[".mpg"] = "video/mpeg";
	_fileExtensionToMediaType[".mov"] = "video/quicktime";
	_fileExtensionToMediaType[".webm"] = "video/webm";
	_fileExtensionToMediaType[".flv"] = "video/x-flv";
	_fileExtensionToMediaType[".m4v"] = "video/x-m4v";
	_fileExtensionToMediaType[".mng"] = "video/x-mng";
	_fileExtensionToMediaType[".asx"] = "video/x-ms-asf";
	_fileExtensionToMediaType[".asf"] = "video/x-ms-asf";
	_fileExtensionToMediaType[".wmv"] = "video/x-ms-wmv";
	_fileExtensionToMediaType[".avi"] = "video/x-msvideo";
}

const std::unordered_map<std::string, MediaType>& MediaConfig::fileExtensionToMediaType() const
{
	return _fileExtensionToMediaType;
}
