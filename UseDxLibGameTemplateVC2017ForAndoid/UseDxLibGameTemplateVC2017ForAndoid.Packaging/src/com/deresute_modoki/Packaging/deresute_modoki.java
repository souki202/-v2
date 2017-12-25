package com.deresute_modoki.Packaging;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.LinearLayout;
import android.app.NativeActivity;
import android.widget.EditText;
import android.app.AlertDialog;
import android.view.View;
import java.lang.Runnable;
import android.widget.VideoView; 
import java.io.*;
import java.lang.Object;
import android.content.*;
import android.widget.LinearLayout;
import android.view.ViewGroup;

public class deresute_modoki extends NativeActivity
{
	NativeActivity act;
	EditText EditView ;
	AlertDialog.Builder AlBuilder ;
	VideoView videoView;
	String dir;

	public void createVideoLayout() {
		File saveDir = getFilesDir();
		dir = saveDir.getPath();
		/*
		videoView = new VideoView(this);
		videoView.getHolder().setFixedSize(1280, 720);
		videoView.setX(100);
		videoView.setY(100);
		this.setContentView(videoView);
		return dir;
		*/
	}

	public String createVideoLayout2() {
		File[] dirArr = getExternalFilesDirs(null);
		dir = dirArr[0].getPath() + "/";
		act = this;
	
		// UIスレッドで実行する処理を登録する
		runOnUiThread( new Runnable ()
		{
		// UIスレッドで呼ばれる関数
			@Override public void run()
			{
				videoView = new VideoView(act);
				videoView.getHolder().setFixedSize(1280, 720);
				videoView.setX(-100);
				videoView.setY(-100);

				videoView.setVideoPath(dir + "Assets/Musics/Trinity Field/bga.ogv");
				act.addContentView(videoView, new LinearLayout.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT,ViewGroup.LayoutParams.FILL_PARENT));
			}
		});
		
		return dir;
	}
}