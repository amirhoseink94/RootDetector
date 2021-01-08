import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;

import java.io.IOException;
import java.util.StringTokenizer;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.NamedNodeMap;

import org.xml.sax.SAXException;

public class XMLFileManager 
{
	public static void extractingData(Node nNode,ArrayList<String> data)
	{
		if(nNode.getNodeName().equals("#text"))
		{
			data.add(nNode.getNodeValue());
		}
		else
		{
			NodeList nlist=nNode.getChildNodes();
			for(int i=0;i<nlist.getLength();i++)
			{
			extractingData(nlist.item(i), data);
			}
		}

	}
	public static void traverse(Node nNode,ArrayList<ArrayList<String>> dataBase)
	{

		NodeList nList=nNode.getChildNodes();

		for(int i=0;i<nList.getLength();i++)
		{

			if(nList.item(i).getNodeName().equals("ArrayOfString")&&nList.item(i).getChildNodes().getLength()==12)
			{
				ArrayList<String> data=new ArrayList<String>();
				extractingData(nList.item(i), data);
				dataBase.add(data);
				System.out.println(data);
			}
			else
				traverse(nList.item(i),dataBase);
		}

	}
	public static ArrayList<ArrayList<String>> extractingDataBase()
	{
		ArrayList<ArrayList<String>> data=new ArrayList<ArrayList<String>>();
		try 
		{
			File fXmlFile = new File("D:\\RootDetector_handler\\test.xml");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);

			doc.getDocumentElement().normalize();

			System.out.println("Root element :" + doc.getDocumentElement().getNodeName());

			NodeList nList = doc.getElementsByTagName("myarray");

			System.out.println("----------------------------");

			for (int temp = 0; temp < nList.getLength(); temp++) 
			{

				Node nNode = nList.item(temp);
				traverse(nNode,data);
				//System.out.println("\nCurrent Element :" + nNode.getNodeName());

				//System.out.println(nNode.get);

			}

		} 
		catch (Exception e) 
		{
			e.printStackTrace();
		}
		return data;
	}
	public static void edit(String s,String name,String address)//not complete yet!!!!!!!!>|<
	{
		try 
		{
			String filepath=new String("Virtual.xml");
			DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
			Document doc = docBuilder.parse(filepath);
			
			doc.getDocumentElement().normalize();

			Node nLibrary=doc.getFirstChild();
			//System.out.println(nLibrary.getNodeName());
			
			int l=nLibrary.getFirstChild().getFirstChild().getLastChild().getChildNodes().getLength();
			
			Element dataPack=doc.createElement("ArrayOfArrayOfString");
			
			Element f_dataPack=doc.createElement("ArrayOfString");
			Element[] nodes=new Element[5];
			for(int i=0;i<5;i++)
				nodes[i]=doc.createElement("string");
			nodes[0].appendChild(doc.createTextNode("DATA1"));
			nodes[1].appendChild(doc.createTextNode("C:\\0Nima\\Visual Basic Projects\\Root Construct (070111)\\bin\\"));
			for(int i=2;i<5;i++)
				nodes[i].appendChild(doc.createTextNode("True"));
			for(int i=0;i<5;i++)
				f_dataPack.appendChild(nodes[i]);
			
			dataPack.appendChild(f_dataPack);
			
			Element l_dataPack=doc.createElement("ArrayOfString");
			Element[] dNode=new Element[5];
			for(int i=0;i<5;i++)
				dNode[i]=doc.createElement("string");
			StringBuffer num=new StringBuffer();
			num.append(l);
			dNode[0].appendChild(doc.createTextNode(num.toString()));
			dNode[1].appendChild(doc.createTextNode(name));
			dNode[2].appendChild(doc.createTextNode(s));
			dNode[3].appendChild(doc.createTextNode(""));
			dNode[4].appendChild(doc.createTextNode(address));
			for(int i=0;i<5;i++)
				l_dataPack.appendChild(dNode[i]);
			
			dataPack.appendChild(l_dataPack);
			
			nLibrary.getFirstChild().getFirstChild().getLastChild().appendChild(l_dataPack);
			
			
			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			DOMSource source = new DOMSource(doc);
			StreamResult result = new StreamResult(new File(filepath));
			transformer.transform(source, result);

			System.out.println("Done");

		} 
		catch (ParserConfigurationException pce) 
		{
			pce.printStackTrace();
		}
		catch (TransformerException tfe) 
		{
			tfe.printStackTrace();
		}
		catch (IOException ioe)
		{
			ioe.printStackTrace();
		} 
		catch (SAXException sae) 
		{
			sae.printStackTrace();
		}
	}
	public static void createXMLFile(String load_address,String save_address)
	{
		try 
		{
			DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder docBuilder = docFactory.newDocumentBuilder();

			// root elements
			Document doc = docBuilder.newDocument();
			Element rootElement = doc.createElement("SerializingObject");
			doc.appendChild(rootElement);

			// staff elements
			Element myarray = doc.createElement("myarray");
			rootElement.appendChild(myarray);

			
			Element AAAS=doc.createElement("ArrayOfArrayOfArrayOfString");
			myarray.appendChild(AAAS);

			Element AAS_null=doc.createElement("ArrayOfArrayOfString");
			AAAS.appendChild(AAS_null);
			Element AAS=doc.createElement("ArrayOfArrayOfString");
			AAAS.appendChild(AAS);

			Element AS_F=doc.createElement("ArrayOfString");
			AAS.appendChild(AS_F);

			Element node=doc.createElement("string");
			node.appendChild(doc.createTextNode("test/1"));
			Element node1=doc.createElement("string");
			node1.appendChild(doc.createTextNode("8"));
			Element node2=doc.createElement("string");
			node2.appendChild(doc.createTextNode("24"));
			Element node3=doc.createElement("string");
			node3.appendChild(doc.createTextNode("/"));
			AS_F.appendChild(node);
			AS_F.appendChild(node1);
			AS_F.appendChild(node2);
			AS_F.appendChild(node3);


			FileReader inputFile=new FileReader(load_address);

			//Instantiate the BufferedReader Class
			BufferedReader bufferReader=new BufferedReader(inputFile);

			//Variable to hold the one line data
			String line;

			// Read file line by line and print on the console

			while ((line = bufferReader.readLine()) != null)   
			{
				StringTokenizer tokenizer=new StringTokenizer(line," ",false);

				String fileAddress="C:\\100-100\\IMG_"+tokenizer.nextToken()+".jpg";
				String date_y=tokenizer.nextToken();
				String tt=tokenizer.nextToken();

				String data_x=tokenizer.nextToken();
				String data_y=tokenizer.nextToken();
				String data_s=tokenizer.nextToken();
				
				StringTokenizer tok=new StringTokenizer(date_y,":",false);
				String y=tok.nextToken();
				String m=tok.nextToken();
				String d=tok.nextToken();
				
				String date=d+"."+m+"."+y+" "+tt;

				Element mData=doc.createElement("ArrayOfString");
				Element[] nData=new Element[14];
				for(int i=0;i<14;i++)
					nData[i]=doc.createElement("string");
				nData[0].appendChild(doc.createTextNode(date));//DATE
				nData[1].appendChild(doc.createTextNode(data_y));
				nData[2].appendChild(doc.createTextNode(fileAddress));
				nData[3].appendChild(doc.createTextNode("0"));
				nData[4].appendChild(doc.createTextNode(data_x));
				nData[5].appendChild(doc.createTextNode("0"));
				nData[6].appendChild(doc.createTextNode("0"));
				nData[7].appendChild(doc.createTextNode(data_x));
				nData[8].appendChild(doc.createTextNode(data_y));
				nData[9].appendChild(doc.createTextNode("ADDRESS"));
				nData[10].appendChild(doc.createTextNode("0"));
				nData[11].appendChild(doc.createTextNode("0"));
				nData[12].appendChild(doc.createTextNode("False"));
				nData[13].appendChild(doc.createTextNode("False"));
				for(int i=0;i<14;i++)
					mData.appendChild(nData[i]);
				AAS.appendChild(mData);

			}
			// write the content into xml file
			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			DOMSource source = new DOMSource(doc);
			StreamResult result = new StreamResult(new File(save_address));

			// Output to console for testing
			// StreamResult result = new StreamResult(System.out);

			transformer.transform(source, result);

			System.out.println("File saved!");

		} 
		catch (ParserConfigurationException pce) 
		{
			pce.printStackTrace();
		} 
		catch (TransformerException tfe) 
		{
			tfe.printStackTrace();
		} 
		catch (Exception e)
		{
			System.out.println("Error while reading file line by line:" + e.getMessage());
		}
	}
	public static void main(String arg[])//0:address file 1:save file 2:number 3:name 4:address in xml file
	{
		//extractingDataBase();
		createXMLFile(arg[0],arg[1]);
		edit(arg[2],arg[3],arg[4]);

	}

}
