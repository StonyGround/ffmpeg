package com.dd.testavprocessing;

import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.net.URLEncoder;

import com.xiuxiu.util.AVProcessing;


import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.util.Base64;
import android.util.Log;
import android.view.Menu;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;

public class MainActivity extends Activity
{
	private final int frameWidth = 640, frameHeight = 480;// 视频帧宽/高
	// private final int frameWidth = 320, frameHeight = 240;// 视频帧宽/高
	private int previewWidth = 0, previewHeight = 0;// 帧预览视图宽/高
	private LinearLayout previewLayout;
	private CameraView cameraView = null;
	private FramePreview framePreview = null;
	
	// BASE64 加密 
    public static  String encryptBase64(String str)
    {
        if (str == null || str.length() == 0)
        {
            return null;
        }
        
        try
        {
            byte[] encode = str.getBytes("UTF-8");
            return new String(Base64.encode(encode, 0, encode.length, Base64.DEFAULT), "UTF-8");
        }
        catch (UnsupportedEncodingException e)
        {
            e.printStackTrace();
        }
  
        return null;  
    }
    
    // BASE64 解密  
    public static  String decryptBase64(String str)
    {
        if (str == null || str.length() == 0)
        {
            return null;
        }
        
        try
        {
            byte[] encode = str.getBytes("UTF-8");
            return new String(Base64.decode(encode, 0, encode.length, Base64.DEFAULT), "UTF-8");
        }
        catch (UnsupportedEncodingException e)
        {
            e.printStackTrace();
        }
  
        return null;
    }
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		Window win = getWindow();
	    win.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
	    
	    // setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		setContentView(R.layout.main);
		
//		String strSrc = "中国";
//		
//		// aes加密/解密
//		String aesStrEn;
//		try
//		{
//			aesStrEn = AES256Cipher.encrypt("12345678", strSrc);
//			Log.d("dd_cc_dd", "aes str en..." + aesStrEn);
//			
//			String aesStrDe = AES256Cipher.decrypt("12345678", aesStrEn);
//			Log.d("dd_cc_dd", "aes str de..." + aesStrDe);
//		}
//		catch (Exception e1)
//		{
//			e1.printStackTrace();
//		}
//		
//		// base64加/解密
//		String strEn = encryptBase64(strSrc);
//		Log.d("dd_cc_dd", "en base64..." + strEn);
//		
//		String strDe = decryptBase64(strEn);
//		Log.d("dd_cc_dd", "de base64..." + strDe);
//		
//		// url加/解密
//		try
//		{
//			String enUrl = URLEncoder.encode(strSrc,"UTF-8");
//			Log.d("dd_cc_dd", "en url..." + enUrl);
//			
//			String deUrl = URLDecoder.decode(enUrl,"UTF-8");
//			Log.d("dd_cc_dd", "de url..." + deUrl);
//		}
//		catch (UnsupportedEncodingException e)
//		{
//			e.printStackTrace();
//		}
		
//		byte[] key = Base64.decode("YWJjZGVmZ2hpamtsbW5vcHFyc3R1dnd4".getBytes(), Base64.DEFAULT);
//        byte[] data = value.getBytes("UTF-8");
//         
//        System.out.println("ECB加密解密");
//        byte[] str3 = Des3.des3EncodeECB(key,data );
//        byte[] str4 = Des3.ees3DecodeECB(key, str3);
//         
//      
//        System.out.println(new String(Base64.encode(str3,  Base64.DEFAULT),"UTF-8"));
//        System.out.println(new String(str4, "UTF-8"));
		
//		// 计算预览视图宽/高
//		DisplayMetrics dm = getResources().getDisplayMetrics();
//      previewWidth = dm.widthPixels;
//      previewHeight = dm.widthPixels;//(int)(dm.heightPixels * 0.8);
//		
//		// 格式转换后的预览图像
//		previewLayout = (LinearLayout)findViewById(R.id.previewLayout);
//		framePreview = new FramePreview(this, frameWidth, frameHeight, previewWidth, previewHeight);
//		LayoutParams params = new LayoutParams(previewWidth, previewHeight);
//		previewLayout.addView(framePreview, params);
//		
//		// 摄像头实时预览图像
//		SurfaceView surfaceView = (SurfaceView)findViewById(R.id.surfaceView);
//		cameraView = new CameraView(surfaceView, framePreview, frameWidth, frameHeight);
		
		
//		String audioFilePath = genrateFilePath("11225566", ".mp4");
//		String videoFilePath = genrateFilePath("1122", ".mp4");
//		String outputFilePath = genrateFilePath("5566", ".mp4");
//		AVProcessing.muxAVFile(audioFilePath, videoFilePath, outputFilePath);
//		Log.d("dd_cc_dd", "....音视频混合完成......");
		
//		String path0 = genrateFilePath("video_5566", ".mp4");
//		String path1 = genrateFilePath("audio_1122", ".mp4");
//		int ret0 = AVProcessing.initVideoEncode(path0, 480, 480);
//		Log.d("dd_cc_dd", "....视频编码初始化 ......" + ret0);
//		int ret1 = AVProcessing.initAudioEncode(path1, 44100, 1);
//		Log.d("dd_cc_dd", "....音频编码初始化 ......" + ret1);
//		
//		int []data = new int[16];
//		int handle = AVProcessing.saveFrame(data, 16);
//		Log.d("dd_cc_dd", "....handle ......" + handle);
		
//		String audioFilePath = genrateFilePath("audio_1122", ".mp4");
		// String audioFilePath = genrateFilePath("test_song", ".mp");
//		String songFilePath = genrateFilePath("6", ".mp3");
//		String outputFilePath = genrateFilePath("output_mix_6666", ".mp4");
//		int ret = AVProcessing.mixAudioWithSong(audioFilePath, songFilePath, outputFilePath);
		// Log.d("dd_cc_dd", "....混音结果 ......" + ret);
		
		
//		String frameFileFolder = Environment.getExternalStorageDirectory() + "/Android/data/xiuxiu/video/video_raw";
//		String outputFilePath0 = Environment.getExternalStorageDirectory() + "/Android/data/xiuxiu/video/dddd.aac";
//		String videoFilePath = Environment.getExternalStorageDirectory() + "/Android/data/xiuxiu/video/dddddddd.mp4";
//		long cur = System.currentTimeMillis();
//		AVProcessing.mergeFrameFiles(frameFileFolder, outputFilePath0);
//		long ddd = System.currentTimeMillis() - cur;
//		Log.d("dd_cc_dd", "....合并文件用时.." + ddd);
//		
//		int frameCountTotal = AVProcessing.initVideoEncode(outputFilePath0, videoFilePath, 480, 480);
//		Log.d("dd_cc_dd", "....frameCountTotal.." + frameCountTotal);
//		
//		if (frameCountTotal > 0)
//		{
//			while (true)
//			{
//				int frameIndex = AVProcessing.encodeVideoFrame();
//				Log.d("dd_cc_dd", "....帧序号..frameIndex.." + frameIndex);
//				if (frameIndex == -1 || frameIndex == frameCountTotal)
//				{
//					AVProcessing.uninitVideoEncode();
//					break;
//				}
//				else
//				{
//					int percent = (int)(95.0f * frameIndex / frameCountTotal);
//					Log.d("dd_cc_dd", "....percent.." + percent);
//				}
//			}// while
//		}
//		else
//		{
//			AVProcessing.uninitVideoEncode();
//		}
		
//		String audioFileFolder = Environment.getExternalStorageDirectory() + "/Android/data/xiuxiu/video/audio_raw";
//		AVProcessing.deleteFiles(audioFileFolder);
//		String outputFilePath1 = Environment.getExternalStorageDirectory() + "/Android/data/xiuxiu/video/merge_audio_000999.mp4";
//		AVProcessing.mergeAudioFiles(audioFileFolder, outputFilePath1);
		
//		String frameFileFolder = Environment.getExternalStorageDirectory() + "/Android/data/xiuxiu/video/video_raw";
//		String frameFilePath = Environment.getExternalStorageDirectory() + "/Android/data/xiuxiu/video/video_raw/1402132963792_frame.raw";
//		String outputFilePad = Environment.getExternalStorageDirectory() + "/Android/data/xiuxiu/video/video_raw/rgb.raw";
//		
//		int frameIndex = 0, frameCount = 0, percent = 0;
//		int width  = 480;
//		int height = 480;
//		frameCount = AVProcessing.initYUV2RGB(frameFileFolder, outputFilePad, width, height);
//		Log.d("dd_cc_dd", "....初始化 ....frameCount.." + frameCount);
//		int curFrameCount = AVProcessing.openFrameFile(frameFilePath, width, height, 0);
//		Log.d("dd_cc_dd", "....初始化 ....curFrameCount.." + curFrameCount);
//		for (int i = 0; i < curFrameCount; i++)
//		{
//			frameIndex = AVProcessing.yuv2rgb();
//			percent = (int)(92.0f * frameIndex / frameCount) + 5;
//		}
//			
//		// 释放资源并删除该视频帧文件
//		AVProcessing.closeFramesRB();
//		AVProcessing.deleteFile(frameFilePath);
//		AVProcessing.uninitYUV2RGB();
		
		// mp4音频文件混合测试
//		String audioFilePath0 = Environment.getExternalStorageDirectory() + "/Android/data/com.xiuxiu/template/video/xiu_audio.mp4";
//		String audioFilePath1 = Environment.getExternalStorageDirectory() + "/Android/data/com.xiuxiu/template/video/t_extract_audio.mp4";
//		String outputFilePath = Environment.getExternalStorageDirectory() + "/Android/data/com.xiuxiu/template/video/output12345.mp4";
//		AVProcessing.mixAudioWithSong2(audioFilePath0, audioFilePath1, outputFilePath, 0.3);
		// /storage/emulated/0/Android/data/com.xiuxiu/template/video/output123.mp4
		
		// 测试音视频分离
//		String videoFilePath = Environment.getExternalStorageDirectory() + "/Android/data/com.xiuxiu/template/video/xlqy.hlv";
//		String v_path = genrateFilePath("t_xiu_extract_video123", ".mp4");
//		String a_path = genrateFilePath("t_xiu_extract_audio123", ".mp4");
//		int ret = AVProcessing.extractAVFile(videoFilePath, v_path, a_path);
//		
//		Log.d("dd_cc_dd", "帧率....." + AVProcessing.getVideoFrameRate(videoFilePath) + "...数据分离结果..." + ret);
		
		// 测试视频解码
		int mainFrameSize = 480 * 480;
		byte[] vYData = null, vUData = null, vVData = null, yuvData = null;
		int qtrFrameSize = mainFrameSize >> 2;
        vYData = new byte[mainFrameSize];
        vUData = new byte[qtrFrameSize];
        vVData = new byte[qtrFrameSize];
        yuvData = new byte[mainFrameSize + qtrFrameSize + qtrFrameSize];
        
		String videoFilePath = Environment.getExternalStorageDirectory() + "/Android/data/com.xiuxiu/test/dahuaxiyou.mp4";
		String videoFilePath2 = Environment.getExternalStorageDirectory() + "/Android/data/com.xiuxiu/test/dahuaxiyou2.mp4";
		int ret = AVProcessing.initVideoDecode(videoFilePath);
		AVProcessing.initVideoEncode(videoFilePath2, 480, 480);
		Log.d("dd_cc_dd", "...ret..." + ret);
		int pktIndex = 0;
		long timeStart = 0;
		double diffTime = 0;
		double sumTimeEn = 0.0, sumTimeDe = 0.0;
		while (true)
		{
			// 解码
			timeStart = System.currentTimeMillis();
			AVProcessing.decodeVideo2Frame(vYData, vUData, vVData, mainFrameSize);
			diffTime = (System.currentTimeMillis() - timeStart) * 0.001;
			sumTimeDe += diffTime;
			// Log.d("dd_cc_dd", "...解码耗时..." + diffTime);
			
			System.arraycopy(vYData, 0, yuvData, 0, mainFrameSize);
			System.arraycopy(vUData, 0, yuvData, mainFrameSize, qtrFrameSize);
			System.arraycopy(vVData, 0, yuvData, mainFrameSize + qtrFrameSize, qtrFrameSize);

			// 编码
			timeStart = System.currentTimeMillis();
			AVProcessing.encodeVideoFrames(yuvData);
			diffTime = (System.currentTimeMillis() - timeStart) * 0.001;
			sumTimeEn += diffTime;
			Log.d("dd_cc_dd", "...编码耗时..." + diffTime);
			
			if (++pktIndex > 150)
			{
				break;
			}
		}
		AVProcessing.uninitVideoDecode();
		AVProcessing.uninitVideoEncode();
		
		pktIndex--;
		Log.d("dd_cc_dd", "...编码平均耗时..." + sumTimeEn / pktIndex);
		Log.d("dd_cc_dd", "...解码平均耗时..." + sumTimeDe / pktIndex);
		
//		new Thread()
//		{
//			@Override
//			public void run()
//			{
//				long timeStart = System.currentTimeMillis();
//				
//				String videoFilePath = Environment.getExternalStorageDirectory() + "/Android/data/com.xiuxiu/video/myly.mp4";
//				String v_path = genrateFilePath("t_decode_xlqy_video", ".raw");
//				String a_path = genrateFilePath("t_decode_xlqy_audio", ".pcm");
//				AVProcessing.decodeVideo2AV(videoFilePath, v_path, a_path);
//				
//				double diffTime = (System.currentTimeMillis() - timeStart) * 0.001;
//				Log.d("dd_cc_dd", "解码耗时...." + diffTime);
//				
//				// 91拍录制的10秒视频 解码要2秒左右，解码后的视频为50M左右
//				// 仙侣奇缘50秒视频 解码要20秒左右，解码后的视频为260M左右
//				// 马云路演30秒视频，解码要10秒左右，解码后视频占用约为148M左右
//			}
//			
//		}.start();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	// 生成文件路径
	public String genrateFilePath(String uniqueId, String fileExtension)
	{
		String fileName = "xiu_" + uniqueId + fileExtension;
		String dirPath = Environment.getExternalStorageDirectory() + "/Android/data/com.xiuxiu/video";
		
		File file = new File(dirPath);
		if (!file.exists() || !file.isDirectory())
		{
			file.mkdirs();
		}
		
		return dirPath + "/" + fileName;
	}
}
