package com.dd.testavprocessing;

import com.xiuxiu.util.AVProcessing;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.Bitmap.Config;
import android.hardware.Camera;
import android.hardware.Camera.PreviewCallback;
import android.util.AttributeSet;
import android.view.View;

public class FramePreview extends View implements PreviewCallback, Runnable
{
	private int[] pixels_rgb;
	byte[] clip_yuv;
	private int frameWidth = 640, frameHeight = 480;// 视频帧宽/高
	private int previewWidth = 0, previewHeight = 0;// 帧预览视图宽/高
	private Bitmap previewBmp = null;
	private Rect previewSrcRect, previewDstRect;
	
	public FramePreview(Context _context)
	{
		super(_context);
	}
	
	public FramePreview(Context _context, AttributeSet _attrs)
	{
		super(_context, _attrs);
	}
	
	public FramePreview(Context _context, int _frameWidth, int _frameHeight, int _previewWidth, int _previewHeight)
	{
		super(_context);
		
		previewWidth = _previewWidth;
		previewHeight = _previewHeight;
		frameWidth = _frameWidth;
		frameHeight =  _frameHeight;
		pixels_rgb = new int[frameWidth * frameHeight];
		int size = frameHeight * frameHeight * 3 / 2;
		clip_yuv = new byte[size];
		previewBmp = Bitmap.createBitmap(frameHeight, frameHeight, Config.ARGB_8888);
		previewSrcRect = new Rect(0, 0, frameHeight, frameHeight);
		previewDstRect = new Rect(0, 0, previewWidth, previewHeight);
		
		// 开启刷新线程
		new Thread(this).start();
	}
	
	@Override
	protected void finalize()
	{
		try
		{
			super.finalize();
		}
		catch (Throwable e)
		{
			e.printStackTrace();
		}
	}
	
	// 绘制
	@Override
	protected void onDraw(Canvas canvas)
	{
		super.onDraw(canvas);

		previewBmp.setPixels(pixels_rgb, 0, frameHeight, 0, 0, frameHeight, frameHeight);
		canvas.drawBitmap(previewBmp, previewSrcRect, previewDstRect, null);
	}
	
	// 实时获取帧视频流数据
	@Override
	public void onPreviewFrame(byte[] data_yuv, Camera camera)
	{
		AVProcessing.rotateClipYUV(data_yuv, clip_yuv, frameWidth, frameHeight, false);
		// AVProcessing.yuv2rgb(clip_yuv, pixels_rgb, frameHeight, frameHeight);
	}
	
	// 刷新线程
	@Override
	public void run()
    {   
        while (!Thread.currentThread().isInterrupted())   
        {   
        	try 
        	{
				Thread.sleep(20);
			} 
        	catch (InterruptedException e)
        	{
				Thread.currentThread().interrupt();
			}
        	
        	// 更新ui
    		postInvalidate();
        }
    } 
}
