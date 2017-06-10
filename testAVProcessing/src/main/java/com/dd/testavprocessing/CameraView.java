package com.dd.testavprocessing;

import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class CameraView implements SurfaceHolder.Callback
{
	private int frameWidth = 640, frameHeight = 480;// 视频帧宽/高
	private Camera camera = null;
	private SurfaceHolder surfaceHolder = null;
	private SurfaceView surfaceView = null;
	private FramePreview previewCallback = null;
	
	public CameraView(SurfaceView _surfaceView, FramePreview _previewCallback, int _frameWidth, int _frameHeight)
	{
		surfaceView = _surfaceView;
		surfaceHolder = surfaceView.getHolder();
		// surfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		surfaceHolder.addCallback(this);
		
		previewCallback = _previewCallback;
		frameWidth = _frameWidth;
		frameHeight = _frameHeight;
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder sh)
	{
		camera = Camera.open();
		Camera.Parameters params = camera.getParameters();
		params.setPreviewSize(frameWidth, frameHeight);
		params.setPreviewFormat(ImageFormat.NV21);// YCbCr_420_SP
		// params.setPictureFormat(ImageFormat.YV12);
		// params.setPreviewFrameRate(10);
		//params.setPreviewFpsRange(10000, 10000);
		camera.setParameters(params);
		// camera.setDisplayOrientation(90);
		camera.setPreviewCallback(previewCallback);
		
		try
		{
			camera.setPreviewDisplay(surfaceHolder);
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
		}
		camera.startPreview();
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder sh, int format, int w, int h)
	{
	}
	
	@Override
	public void surfaceDestroyed(SurfaceHolder sh)
	{
		releaseCamera();
	}
	
	// 开启摄像头
	public void startPreview()
	{
		if (camera != null)
		{
			camera.startPreview();
		}
	}
	
	// 关闭摄像头
	public void stopPreview()
	{
		if (camera != null)
		{
			camera.stopPreview();
		}
	}
	
	// 释放摄像头
	public void releaseCamera()
	{
		if (camera != null)
		{
			camera.setPreviewCallback(null);
			camera.stopPreview();
			camera.release();
			camera = null;
		}
	}
}
