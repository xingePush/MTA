Pod::Spec.new do |spec|
  spec.name						= "QQ_MTA"
  spec.version					= "2.7.0"
  spec.summary					= "腾讯移动分析（MTA）"
  spec.homepage					= "http://mta.qq.com"
  spec.authors					= "tencent TEG"
  spec.license					= "MIT"
  spec.platform					= :ios, "8.0"
  spec.source					= {:git => "https://github.com/xingePush/MTA.git", :tag => "v#{spec.version}"}
  spec.default_subspec			= 'BasicAnalysis'

  spec.subspec 'BasicAnalysis' do |ba|
    ba.vendored_libraries		= "MTA/*.a"
    ba.source_files				= "MTA/*.h"
    ba.public_header_files		= "MTA/*.h"
    ba.frameworks				= "Security","CFNetwork","SystemConfiguration","CoreTelephony"
    ba.libraries				= "z", "sqlite3"
  end

  spec.subspec 'Hybrid' do |hy|
    hy.dependency				'QQ_MTA/BasicAnalysis'
    hy.vendored_libraries		= "MTA/plugin/MTAHybrid/*.a"
    hy.source_files				= "MTA/plugin/MTAHybrid/*.h"
    hy.public_header_files		= "MTA/plugin/MTAHybrid/*.h"
  end

end
