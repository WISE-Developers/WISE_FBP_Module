package ca.wise.serialize;

public class SerializeProtoOptions {

	private boolean verboseOutput = false;
	
	public SerializeProtoOptions() { }
	
	public boolean useVerboseOutput() { return verboseOutput; }
	
	public void setVerboseOutput(boolean value) { verboseOutput = value; }
}
