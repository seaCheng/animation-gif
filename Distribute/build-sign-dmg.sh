#！/bin/bash


#使用说明：
#此shell脚本，python脚本，与APP文件放在同一文件夹后运行

app_name=animationGif
app_location=animationGif/animationGif.app

dev_acc=407446947@qq.com
dev_pwd=**********
dev_team="Developer ID Application: Haiyang Cheng (******)"
dev_entitlements=animationGif.entitlements
bundle_id="com.sea.animationGif"

#./AnkerWork/AnkerWork.app/Contents/MacOS/AnkerWork
pkg_exec="$app_name/$app_name.app/Contents/MacOS/$app_name"
python_script=macdeployqtfix.py
qt_path=/Users/sea/Qt/6.2.4

mkdir animationGif

cp -R animationGif.app $app_name

ln -s /Applications/ $app_name

#/Users/sea/Qt/6.2.4/macos/bin
/Users/sea/Qt/6.2.4/macos/bin/macdeployqt $app_location

python $python_script $pkg_exec $qt_path

codesign -dvv --verbose=4 -f -s $dev_team -v $app_location --deep --entitlements $dev_entitlements -o runtime

hdiutil create animationGif.dmg -ov -volname $app_name -fs HFS+ -srcfolder $app_name

rm -rf $app_name

res_file="/tmp/result.tmp"
uuid_file="/tmp/uuid.tmp"

xcrun altool --notarize-app -f "animationGif.dmg" --primary-bundle-id $bundle_id -u $dev_acc -p $dev_pwd > $uuid_file

#if [ $upload_result == 0 ];then
UUID=$(grep "RequestUUID" $uuid_file|awk '{print $3}')

if [ "$UUID" != "" ]; then
echo "---> Checking $UUID"

while true; do
xcrun altool --notarization-info $UUID -u $dev_acc -p $dev_pwd > $res_file
exist=$(grep -c "Status Message: Package Approved" $res_file)
echo "num is $exist"
if [ $exist -gt 0 ]; then
echo "---> Package Approved!!!"
break
else
echo "---> Package Processing!!!"
fi
done
#complete
xcrun stapler staple animationGif.dmg
echo "---> Upload Complete!!!"
else
echo "---> UUID ERROR!!!"
fi
#else
#    echo "---> Upload Package Error!!!"
#fi


#dev_acc=407446947@qq.com dev_pwd=cgre-oowm-jpmi-cycg
#上传成功后通过返回的request id进行查询审核状态
#xcrun altool --notarization-info eb865fd7-ff9f-4ae1-b740-0f21b0374991 -u "407446947@qq.com" -p "cgre-oowm-jpmi-cycg"
#收到返回package approved消息后调用以下命令包装
#xcrun stapler staple animationGif.dmg


