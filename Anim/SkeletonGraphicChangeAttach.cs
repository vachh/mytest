using System.Collections.Generic;
using UnityEngine;
using Spine.Unity.AttachmentTools;
using Spine.Unity;
using Spine;
using System;
using Newtonsoft.Json;

public class SkeletonGraphicChangeAttach : MonoBehaviour {

	public SkeletonGraphic skeletonGraphic;
	[SpineSkin]
	public string baseSkinName = "default";
	public List<AttachData> datas;
	public bool useCacheAttachment = true;
	
	[Header("赋值")]
	public Texture2D runtimeAtlas;
	public Material runtimeMaterial;

	private Skin baseSkin;
	private Skeleton skeleton;
	private Material sourceMaterial;
	private Skin customSkin;
	private static Dictionary<int, Attachment> attachCaches = new Dictionary<int, Attachment>();
	private void Awake() {
		skeleton = skeletonGraphic.Skeleton;
		baseSkin = skeleton.Data.FindSkin(baseSkinName);
		sourceMaterial = skeletonGraphic.SkeletonDataAsset.atlasAssets[0].PrimaryMaterial;

		customSkin = new Skin("custom skin");
	}

	[EditorButton]
	private void testApply() {
		Apply(datas, useCacheAttachment);
	}

	public void Apply (List<AttachData> datas, bool canUseCacheAttachment) {
		if(datas == null)
			return;
		this.datas = datas;
		
		customSkin.Clear();
		foreach (var data in datas)
		{
			int visorSlotIndex = skeleton.FindSlotIndex(data.slotName);
			if(canUseCacheAttachment && attachCaches.ContainsKey(data.id)){
				customSkin.SetAttachment(visorSlotIndex, data.attachName, attachCaches[data.id]);
			}else{

				Attachment baseAttachment = baseSkin.GetAttachment(visorSlotIndex, data.attachName);
				Attachment newAttachment = baseAttachment.GetRemappedClone(data.sprite, sourceMaterial);
				customSkin.SetAttachment(visorSlotIndex, data.attachName, newAttachment);

				if(canUseCacheAttachment)
					attachCaches[data.id] = newAttachment;
			}
		}
		
		//合并贴图，SkeletonGraphic 必须合并
		var repackedSkin = new Skin("repacked skin");
		repackedSkin.AddAttachments(baseSkin);
		if(customSkin.Attachments.Count > 0)
			repackedSkin.AddAttachments(customSkin);

		if (runtimeMaterial)
			Destroy(runtimeMaterial);
		if (runtimeAtlas)
			Destroy(runtimeAtlas);
		
		repackedSkin = repackedSkin.GetRepackedSkin("repacked skin", sourceMaterial, out runtimeMaterial, out runtimeAtlas, 2048);
		skeleton.SetSkin(repackedSkin);

		skeleton.SetToSetupPose();
		skeletonGraphic.Update(0);
		skeletonGraphic.OverrideTexture = runtimeAtlas;

		AtlasUtilities.ClearCache();
	}
}

[Serializable]
public class AttachData{
	[Header("配置表id")]
	public int id;
	public Sprite sprite;
	[SpineSkin]
	public string baseSkinName = "default";
	[SpineSlot]
	public string slotName;
	[SpineAttachment(slotField: "slotName", skinField: "baseSkinName")]
	public string attachName;
	[JsonIgnore]
	public int _type; //更换时使用
}