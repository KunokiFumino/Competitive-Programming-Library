using System.Collections;
namespace cpcm
{

    class Node
    {
        public Int32 f;
        public String name, path;
        public ArrayList subs = new ArrayList();
        public ArrayList dependences = new ArrayList();
    }

    public partial class Form1 : Form
    {
        private Node[] nodes;
        private ArrayList copied;
        private Int32 n;
        private String code;
        public Form1()
        {
            try
            {
                StreamReader streamReader = new StreamReader(@"config.txt");
                String line;
                line = streamReader.ReadLine();
                n = Convert.ToInt32(line);
                nodes = new Node[n];
                Int32 i, j;
                for (i = 0; i < n; i++)
                {
                    nodes[i] = new Node();

                    line = streamReader.ReadLine();
                    line = streamReader.ReadLine();
                    Int32 f = Convert.ToInt32((string)line);
                    nodes[i].f = f;
                    if (f != -1) nodes[f].subs.Add(i);

                    nodes[i].name = streamReader.ReadLine();

                    nodes[i].path = streamReader.ReadLine();

                    line = streamReader.ReadLine();
                    Int32 m = Convert.ToInt32((string)line);
                    for (j = 0; j < m; j++)
                    {
                        line = streamReader.ReadLine();
                        nodes[i].dependences.Add(line);
                    }
                }
                streamReader.Close();
            } catch {
                MessageBox.Show("Can't find config.txt or it has syntax error.");
                Environment.Exit(-1);
            }
            InitializeComponent();
        }

        private void recursivelyAdd(String name)
        {
            if (copied.Contains(name)) return;
            copied.Add(name);
            bool find = false;
            for (Int32 i = 0; i < n; i++)
            {
                if (nodes[i].name == name)
                {
                    find = true;
                    foreach (String d in nodes[i].dependences) recursivelyAdd(d);
                    try
                    {
                        StreamReader streamReader = new StreamReader(nodes[i].path);
                        code += streamReader.ReadToEnd() + "\n";
                        streamReader.Close();
                    } catch {
                        MessageBox.Show("Can't find file [" + nodes[i].path + "].");
                    }
                    break;
                }
            }
            if (!find) MessageBox.Show("Can't find module [" + name + "].");
        }

        private void recursivelyAdd(TreeNode t)
        {
            if (t.GetNodeCount(false) > 0)
            {
                for (int i = 0; i < t.Nodes.Count; i++)
                {
                    recursivelyAdd(t.Nodes[i]);
                }
            }
            else if (t.Checked) recursivelyAdd(t.Name);
        }

        private void recursivelyUncheck(TreeNode t)
        {
            t.Checked = false;
            if (t.GetNodeCount(false) > 0)
            {
                for (int i = 0; i < t.Nodes.Count; i++)
                {
                    recursivelyUncheck(t.Nodes[i]);
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            copied = new ArrayList();
            code = "";
            for (Int32 i = 0; i < treeView1.Nodes.Count; i++) recursivelyAdd(treeView1.Nodes[i]);
            if (code != "") Clipboard.SetText(code);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            for (Int32 i = 0; i < treeView1.Nodes.Count; i++) recursivelyUncheck(treeView1.Nodes[i]);
        }
    }
}