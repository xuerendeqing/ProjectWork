package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxHandler.DialogMessage;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

public class AppActivity extends Cocos2dxActivity{
	public static final int SHOW_DIALOG = 0x0001;
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		JniTestHelper.init(mHandler);
		JniTestHelper.setPackageName(this.getPackageName());
	}
	
	public Cocos2dxGLSurfaceView onCreateView(){
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		glSurfaceView.setEGLConfigChooser(5,6,5,0,16,8);
		return glSurfaceView;
	}
	static {
		System.loadLibrary("cocos2dcpp");
	}
	
	private Handler mHandler = new Handler()
	{
		public void handleMessage(Message msg) {
			
			switch (msg.what)
			{
			case SHOW_DIALOG:
				DialogMessage dm = (DialogMessage)msg.obj;
				new AlertDialog.Builder(AppActivity.this)
				.setTitle(dm.titile)
				.setMessage(dm.message).setNegativeButton("cancle", new DialogInterface.OnClickListener() {
					
					@Override
					public void onClick(DialogInterface arg0, int arg1) {
						// TODO Auto-generated method stub
						arg0.dismiss();
					}
				})
				.setPositiveButton("Ok",new DialogInterface.OnClickListener(){
					public void onClick(DialogInterface arg0, int arg1) {
						arg0.dismiss();
						JniTestHelper.exitApp();
					}
				})
				.create().show();
				break;
			}
		}
	};
}