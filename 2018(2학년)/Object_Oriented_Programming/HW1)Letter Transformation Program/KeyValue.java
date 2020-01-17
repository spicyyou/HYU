package assignment;
import java.util.StringTokenizer;

public class KeyValue {
	private String key;
	private String value;
	
	public KeyValue() {
	}
	public KeyValue(String input) {
		StringTokenizer st = new StringTokenizer(input,"=");
		key=st.nextToken();
		value=st.nextToken();
	}

	String getKey() {
		return key;
	}
	
	String getValue() {
		return value;
	}
}
