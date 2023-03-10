#include "MediaType.h"

#include <unordered_map>
#include "utils/exceptions/ParsingException.h"

MediaType MediaType::Default = MediaType("text/html");
MediaType MediaType::Html = MediaType("text/html");

MediaType MediaType::fromFileExtension(const std::string& fileExtension)
{
	static std::unordered_map<std::string, MediaType> types;
	if (types.empty())
	{
		types[".html"] = "text/html";
		types[".htm"] = "text/html";
		types[".shtml"] = "text/html";
		types[".css"] = "text/css";
		types[".xml"] = "text/xml";
		types[".gif"] = "image/gif";
		types[".jpeg"] = "image/jpeg";
		types[".jpg"] = "image/jpeg";
		types[".js"] = "application/javascript";
		types[".atom"] = "application/atom+xml";
		types[".rss"] = "application/rss+xml";

		types[".mml"] = "text/mathml";
		types[".txt"] = "text/plain";
		types[".jad"] = "text/vnd.sun.j2me.app-descriptor";
		types[".wml"] = "text/vnd.wap.wml";
		types[".htc"] = "text/x-component";

		types[".png"] = "image/png";
		types[".svg"] = "image/svg+xml";
		types[".svgz"] = "image/svg+xml";
		types[".tif"] = "image/tiff";
		types[".tiff"] = "image/tiff";
		types[".wbmp"] = "image/vnd.wap.wbmp";
		types[".webp"] = "image/webp";
		types[".ico"] = "image/x-icon";
		types[".jng"] = "image/x-jng";
		types[".bmp"] = "image/x-ms-bmp";

		types[".woff"] = "font/woff";
		types[".woff2"] = "font/woff2";

		types[".jar"] = "application/java-archive";
		types[".war"] = "application/java-archive";
		types[".ear"] = "application/java-archive";
		types[".json"] = "application/json";
		types[".hqx"] = "application/mac-binhex40";
		types[".doc"] = "application/msword";
		types[".pdf"] = "application/pdf";
		types[".ps"] = "application/postscript";
		types[".eps"] = "application/postscript";
		types[".ai"] = "application/postscript";
		types[".rtf"] = "application/rtf";
		types[".m3u8"] = "application/vnd.apple.mpegurl";
		types[".kml"] = "application/vnd.google-earth.kml+xml";
		types[".kmz"] = "application/vnd.google-earth.kmz";
		types[".xls"] = "application/vnd.ms-excel";
		types[".eot"] = "application/vnd.ms-fontobject";
		types[".ppt"] = "application/vnd.ms-powerpoint";
		types[".odg"] = "application/vnd.oasis.opendocument.graphics";
		types[".odp"] = "application/vnd.oasis.opendocument.presentation";
		types[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
		types[".odt"] = "application/vnd.oasis.opendocument.text";

		types[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
		types[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
		types[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";

		types[".wmlc"] = "application/vnd.wap.wmlc";
		types[".7z"] = "application/x-7z-compressed";
		types[".cco"] = "application/x-cocoa";
		types[".jardiff"] = "application/x-java-archive-diff";
		types[".jnlp"] = "application/x-java-jnlp-file";
		types[".run"] = "application/x-makeself";
		types[".pl"] = "application/x-perl";
		types[".pm"] = "application/x-perl";
		types[".prc"] = "application/x-pilot";
		types[".pdb"] = "application/x-pilot";
		types[".rar"] = "application/x-rar-compressed";
		types[".rpm"] = "application/x-redhat-package-manager";
		types[".sea"] = "application/x-sea";
		types[".swf"] = "application/x-shockwave-flash";
		types[".sit"] = "application/x-stuffit";
		types[".tcl"] = "application/x-tcl";
		types[".tk"] = "application/x-tcl";
		types[".der"] = "application/x-x509-ca-cert";
		types[".pem"] = "application/x-x509-ca-cert";
		types[".crt"] = "application/x-x509-ca-cert";
		types[".xpi"] = "application/x-xpinstall";
		types[".xhtml"] = "application/xhtml+xml";
		types[".xspf"] = "application/xspf+xml";
		types[".zip"] = "application/zip";

		types[".bin"] = "application/octet-stream";
		types[".exe"] = "application/octet-stream";
		types[".dll"] = "application/octet-stream";
		types[".deb"] = "application/octet-stream";
		types[".dmg"] = "application/octet-stream";
		types[".iso"] = "application/octet-stream";
		types[".img"] = "application/octet-stream";
		types[".msi"] = "application/octet-stream";
		types[".msp"] = "application/octet-stream";
		types[".msm"] = "application/octet-stream";

		types[".mid"] = "audio/midi";
		types[".midi"] = "audio/midi";
		types[".kar"] = "audio/midi";
		types[".mp3"] = "audio/mpeg";
		types[".ogg"] = "audio/ogg";
		types[".m4a"] = "audio/x-m4a";
		types[".ra"] = "audio/x-realaudio";

		types[".3gpp"] = "video/3gpp";
		types[".3gp"] = "video/3gpp";
		types[".ts"] = "video/mp2t";
		types[".mp4"] = "video/mp4";
		types[".mpeg"] = "video/mpeg";
		types[".mpg"] = "video/mpeg";
		types[".mov"] = "video/quicktime";
		types[".webm"] = "video/webm";
		types[".flv"] = "video/x-flv";
		types[".m4v"] = "video/x-m4v";
		types[".mng"] = "video/x-mng";
		types[".asx"] = "video/x-ms-asf";
		types[".asf"] = "video/x-ms-asf";
		types[".wmv"] = "video/x-ms-wmv";
		types[".avi"] = "video/x-msvideo";
	}

	std::unordered_map<std::string, MediaType>::iterator i = types.find(fileExtension);
	if (i == types.end())
		throw ParsingException("Unsupported media type: " + fileExtension);

	return i->second;
}

MediaType::MediaType()
{
}

MediaType::MediaType(const std::string& string) : std::string(string)
{
}

MediaType::MediaType(const char* string) : std::string(string)
{
}