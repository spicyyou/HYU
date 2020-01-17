package assignment;

import assignment.KeyValue;
import java.io.*;

public class LetterTrasformator {
	public static void main(String[] args) {
		try {
			FileInputStream fis = new FileInputStream("template_file.txt");
			FileOutputStream fos = new FileOutputStream("output_file.txt");
			String str = "";
			String str_prop=null;
			int ch;
			// template find
			while ((ch = fis.read()) != -1) {
				if ((char) ch != '{') {
					fos.write((byte) ch);
					
				} else {
					str="";
					while ((ch = fis.read()) != -1) {
						if ((char) ch != '}') {
							str += (char) ch;
						}
						else break;
					}
					FileReader fReader_prop = new FileReader("properties.txt");
					BufferedReader bReader_prop = new BufferedReader(fReader_prop);
					while ((str_prop = bReader_prop.readLine()) != null) {
						KeyValue k = new KeyValue(str_prop);
						if (k.getKey().equals(str)) {
							String temp = k.getValue();
							int i;
							for (i = 0; i < temp.length(); i++) {
								fos.write((byte) temp.charAt(i));
							}
							break;
						}
					}
					fReader_prop.close();
					bReader_prop.close();
					
				}
			}
			fis.close();
			fos.close();
		} catch (IOException e) {
			System.err.println(e);
			System.exit(1);
		}
	}
}
