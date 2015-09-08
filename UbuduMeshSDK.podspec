Pod::Spec.new do |s|
  s.name         = "UbuduMeshSDK"
  s.version      = "1.0"
  s.summary      = "Mesh SDK allows devices to send messages through the mesh network."
  s.homepage     = "http://www.ubudu.com"
  s.license      = { :type => "BSD", :file => "LICENSE" }
  s.author       = { "Ubudu SAS" => "cocoapods@ubudu.com" }
  s.social_media_url = "https://twitter.com/Ubudu"

  s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/Ubudu/IOS-Mesh-SDK.git", :tag => "v1.0" }
  s.vendored_frameworks = "UbuduMeshSDK.framework"
  s.frameworks = "Foundation", "CoreBluetooth"

  s.requires_arc = true
  s.xcconfig = { "OTHER_LDFLAGS" => "" }
end
