/*
 * @Author: 家
 * @QQ: 203118908
 * @bilibili: 晓宇小凡
 * @versioin: 1.0
 * @Date: 2020-05-02 23:15:47
 * @LastEditTime: 2020-05-03 03:07:52
 * @LastEditors: 家
 * @Description: so中执行autojs脚本
 * @FilePath: \autojsNativeJs\nativeJs\main.js
 * @学习格言: 即用即学, 即学即用
 * @加密方法是 内个球  which_who@qq.com(1366505103)  2020/05/02 23:08:50 制作完成
 */
var ctx = context;
var cwd = files.cwd();
var dexpath=cwd+"/classes.dex"
var sopath=cwd+"/libjni.so"
log('dexpath = '+dexpath)
log('sopath = '+sopath)
var jnipath=ctx.getDir("libs", android.app.Activity.MODE_PRIVATE);
log('jnipath = '+jnipath)
var dirpath=ctx.getDir("dex", android.app.Activity.MODE_PRIVATE).getAbsolutePath();
log('dirpath = '+dirpath)
copy(sopath, new java.io.File(jnipath, "libjni.so").getAbsolutePath());
var dcl=new Packages.dalvik.system.DexClassLoader(dexpath, dirpath, jnipath, java.lang.ClassLoader.getSystemClassLoader());

var cls=dcl.loadClass("com.jia.nativejs.Main")
var api=cls.newInstance()
api.init(ctx.getClass().getClassLoader());

function copy(f, t){
	var fip = new java.io.FileInputStream(f).getChannel();
	var fop = new java.io.FileOutputStream(t).getChannel();
	fip.transferTo(0, fip.size(), fop);
	fip.close();fop.close();
}
