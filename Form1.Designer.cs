using System.Collections;
namespace cpcm
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.TreeNode[] tree_nodes = new System.Windows.Forms.TreeNode[n];
            Int32[] d = new Int32[n];
            Queue<Int32> q = new Queue<Int32>();
            Int32 i, j;
            ArrayList roots = new ArrayList();
            for (i = 0; i < n; i++)
            {
                d[i] = nodes[i].subs.Count;
                if (d[i] == 0) q.Enqueue(i);
                if (nodes[i].f == -1) roots.Add(i);
            }

            while (q.Count > 0)
            {
                i = q.Dequeue();
                if (nodes[i].subs.Count > 0)
                {
                    System.Windows.Forms.TreeNode[] subs = new System.Windows.Forms.TreeNode[nodes[i].subs.Count];
                    j = 0;
                    foreach (Int32 k in nodes[i].subs)
                    {
                        subs[j] = tree_nodes[k];
                        j++;
                    }
                    tree_nodes[i] = new System.Windows.Forms.TreeNode(nodes[i].name, subs);
                }
                else tree_nodes[i] = new System.Windows.Forms.TreeNode(nodes[i].name);
                tree_nodes[i].Name = nodes[i].name;
                tree_nodes[i].Text = "[#" + i.ToString() + "] " + nodes[i].name;
                if (nodes[i].f != -1)
                {
                    d[nodes[i].f]--;
                    if (d[nodes[i].f] == 0) q.Enqueue(nodes[i].f);
                }
            }

            System.Windows.Forms.TreeNode[] rootsArray = new System.Windows.Forms.TreeNode[roots.Count];
            j = 0;
            foreach (Int32 k in roots)
            {
                rootsArray[j] = tree_nodes[k];
                j++;
            }
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Constantia", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button1.Location = new System.Drawing.Point(12, 188);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(202, 103);
            this.button1.TabIndex = 0;
            this.button1.Text = "copy to clipboard";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("Constantia", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button2.Location = new System.Drawing.Point(311, 188);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(200, 103);
            this.button2.TabIndex = 1;
            this.button2.Text = "uncheck all";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // treeView1
            // 
            this.treeView1.CheckBoxes = true;
            this.treeView1.Nodes.AddRange(rootsArray);
            this.treeView1.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.treeView1.Location = new System.Drawing.Point(12, 12);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(499, 170);
            this.treeView1.TabIndex = 2;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(523, 302);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "cpcm";
            this.ResumeLayout(false);

        }

        #endregion

        private Button button1;
        private Button button2;
        private TreeView treeView1;
    }
}