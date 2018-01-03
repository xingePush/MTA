Pod::Spec.new do |spec|
  spec.name						= "QQ_MTA"
  spec.version					= "2.1.2"
  spec.summary					= "腾讯移动分析（MTA）"
  spec.homepage					= "http://mta.qq.com"
  spec.authors					= "tencent TEG"
  spec.license					= "MIT"
  spec.platform					= :ios, "8.0"
  spec.source					= { :git => "https://github.com/tegdata/MTA.git", :tag => spec.version }
  spec.default_subspec			= 'BasicAnalysis'

  spec.subspec 'BasicAnalysis' do |ba|
    ba.vendored_libraries		= "MTA/*.a"
    ba.source_files				= "MTA/*.h"
    ba.public_header_files		= "MTA/*.h"
    ba.frameworks				= "Security","CFNetwork","SystemConfiguration","CoreTelephony"
    ba.libraries				= "z", "sqlite3"
  end

  spec.subspec 'AutoTrack' do |at|
    at.dependency				'QQ_MTA/BasicAnalysis'
    at.vendored_libraries		= "MTA/plugin/autotrack/*.a"
    at.source_files				= "MTA/plugin/autotrack/*.h"
    at.public_header_files		= "MTA/plugin/autotrack/*.h"
  end

  spec.subspec 'Hybrid' do |hy|
    hy.dependency				'QQ_MTA/BasicAnalysis'
    hy.vendored_libraries		= "MTA/plugin/hybrid/*.a"
    hy.source_files				= "MTA/plugin/hybrid/*.h"
    hy.public_header_files		= "MTA/plugin/hybrid/*.h"
  end

  spec.subspec 'Idfa' do |idfa|
    idfa.dependency				'QQ_MTA/BasicAnalysis'
    idfa.vendored_libraries		= "MTA/plugin/idfa/*.a"
    idfa.frameworks				= "AdSupport"
  end

  spec.subspec 'InstallTracker' do |it|
    it.dependency				'QQ_MTA/BasicAnalysis'
    it.vendored_libraries		= "MTA/plugin/installtracker/*.a"
    it.source_files				= "MTA/plugin/installtracker/*.h"
    it.public_header_files		= "MTA/plugin/installtracker/*.h"
  end
end
