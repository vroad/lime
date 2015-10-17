package org.nodejs;

import android.util.Log;


// Wrapper for nodejs


public class NodeJS {
	
	
	private static boolean mInit = false;
	
	
	private static native int start (String argv[], String workDir, String logFilePath);
	
	
	public static int run (String argv[], String workDir, String logFilePath) {
		
		if (!mInit) {
			
			mInit = true;
			System.loadLibrary ("node");
			
		}
		
		return start (argv, workDir, logFilePath);
		
	}
	
	
}